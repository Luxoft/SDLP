/**
 *
 * SDLP SDK
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 *
 * Copyright (C) 2013, Luxoft Professional Corp., member of IBS group
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *
 */
/**
 * @author Elena Bratanova <ebratanova@luxoft.com>
 */

#include <cstdlib>
#include <string.h>
#include "Logger.hpp"

#include "ZmqSocket/ZmqSocketsRegister.h"
#include "ZmqSocket/SenderZmqSocket.h"

using namespace NsUtils;

Logger ZmqSocketsRegister::mLogger = Logger::getInstance("Utils.ZmqSocket.ZmqSocketsRegister");

ZmqSocketsRegister::ZmqSocketsRegister(void * context)
    : mZmqContext(context)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_mutex_init(&mSocketsMutex, NULL);
}

ZmqSocketsRegister::~ZmqSocketsRegister()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_mutex_lock(&mSocketsMutex);
    tSocketsMap::iterator iter = mSockets.begin();
    while (iter != mSockets.end())
    {
        if (iter->second != NULL)
        {
            delete iter->second;
        }
        iter ++;
    }
    mSockets.clear();
    pthread_mutex_unlock(&mSocketsMutex);
    pthread_mutex_destroy(&mSocketsMutex);
}

bool ZmqSocketsRegister::createSocketForClient(std::string const& clientName, SocketConnectionType type)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_mutex_lock(&mSocketsMutex);
    if (mSockets.find(clientName) != mSockets.end())
    {
        LOG4CPLUS_WARN(mLogger, "Socket already exists");
        return false;
    }
    SenderZmqSocket * newSock = new SenderZmqSocket(mZmqContext, ZMQ_PROTOCOL_PREFIX + clientName, type);
    mSockets[clientName] = newSock;
    if (mPendingMessages.find(clientName) == mPendingMessages.end())
    {
        pthread_mutex_unlock(&mSocketsMutex);
        return true;
    }
    tPendingMessagesList pending = mPendingMessages[clientName];
    for (tPendingMessagesList::iterator iter = pending.begin(); iter != pending.end(); iter ++)
    {
        newSock->pushMessageToQueue(iter->first, iter->second);
        delete[] iter->second;
    }
    mPendingMessages.erase(clientName);
    pthread_mutex_unlock(&mSocketsMutex);
    return true;
}

bool ZmqSocketsRegister::destroySocketForClient(std::string const& clientName)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_mutex_lock(&mSocketsMutex);
    tSocketsMap::iterator iter = mSockets.find(clientName);
    bool res = true;
    if (iter != mSockets.end())
    {
        delete iter->second;
        mSockets.erase(iter);
    }
    else
    {
        res = false;
        LOG4CPLUS_ERROR(mLogger, "no socket for " + clientName + ", nothing to erase");
    }
    pthread_mutex_unlock(&mSocketsMutex);
    return res;
}


bool ZmqSocketsRegister::sendMessageToClient(std::string const& clientName,
            const unsigned int dataSize, const char * const data)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_mutex_lock(&mSocketsMutex);
    tSocketsMap::iterator iter = mSockets.find(clientName);
    bool res = true;
    if (iter != mSockets.end())
    {
        iter->second->pushMessageToQueue(dataSize, data);
    }
    else
    {
        res = false;
        LOG4CPLUS_WARN(mLogger, "no socket for " + clientName + ", cannot send anything");
        char * dataCopy = new char[dataSize];
        memcpy(dataCopy, data, dataSize);
        mPendingMessages[clientName].push_back(std::make_pair(dataSize, dataCopy));
    }
    pthread_mutex_unlock(&mSocketsMutex);
    return res;
}
