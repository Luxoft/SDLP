/*
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

/*
 *  File:   ZmqServer.cpp
 *
 *  Author: Vyacheslav Plachkov
 */


#include <cassert>
#include <cstring>

#include "ZmqSocket/ZmqServer.h"
#include "ZmqSocket/ZmqSocketsRegister.h"

using namespace NsUtils;

Logger ZmqServer::mLogger = Logger::getInstance("Utils.ZmqSocket.ZmqServer");

ZmqServer::ZmqServer(const std::string &serverName, IServerListener * listener)
    : mZmqContext(NULL)
    , mSockets(NULL)
    , mReceiverSocket(NULL)
    , mServerName(serverName)
    , mServerAddress(ZMQ_PROTOCOL_PREFIX + serverName)
    , mListener(listener)
    , mClientCounter(0)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    pthread_mutex_init(&mClientsMapMutex, NULL);

    mZmqContext = zmq_ctx_new();
    mSockets = new ZmqSocketsRegister(mZmqContext);
    mReceiverSocket = new ReceiverZmqSocket(mZmqContext, mServerAddress, BIND, this);
}

ZmqServer::~ZmqServer()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    delete mReceiverSocket;
    delete mSockets;
    zmq_ctx_destroy(mZmqContext);
    pthread_mutex_destroy(&mClientsMapMutex);
}

bool ZmqServer::sendMessageToClient(const std::string & clientName,
        const char * data, const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (dataSize <= 0 || data == NULL)
    {
        LOG4CPLUS_ERROR(mLogger, "Not sending empty message!");
        return false;
    }
    ZmqClientServerMessage msg;
    msg.isControlMessage = false;
    msg.dataSize = dataSize;
    char buf[sizeof(ZmqClientServerMessage) + dataSize];
    memcpy(buf, &msg, sizeof(ZmqClientServerMessage));
    memcpy(buf + sizeof(ZmqClientServerMessage), data, dataSize);
    return mSockets->sendMessageToClient(clientName, sizeof(buf), buf);
}

void ZmqServer::handleMessage(tSizedMessage message)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (message.first < sizeof(ZmqClientServerMessage))
    {
        LOG4CPLUS_ERROR(mLogger, "Message is too small to be valid: " << message.first);
        return;
    }
    ZmqClientServerMessage * msg = reinterpret_cast<ZmqClientServerMessage*>((char*)message.second);
    const char * data = message.second + sizeof(ZmqClientServerMessage);
    if (message.first < sizeof(ZmqClientServerMessage) + msg->dataSize)
    {
        LOG4CPLUS_ERROR(mLogger, "Message is inconsistent");
        return;
    }

    if (msg->isControlMessage == true)
    {
        handleHelloRequest(data, msg->dataSize);
    }
    else 
    {
        pthread_mutex_lock(&mClientsMapMutex);
        std::string clientName;
        if (mClientIdMap.find(msg->clientID) == mClientIdMap.end())
        {
            LOG4CPLUS_ERROR(mLogger, "Unknown client id: " << msg->clientID);
            pthread_mutex_unlock(&mClientsMapMutex);
            return;
        }
        clientName = mClientIdMap[msg->clientID];
        pthread_mutex_unlock(&mClientsMapMutex);

        if (mListener)
        {
            mListener->onMessageReceived(msg->dataSize, data, clientName);
        }
    }
}

void ZmqServer::handleHelloRequest(char const * const data, const unsigned int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (dataSize == 0 || data == NULL)
    {
        LOG4CPLUS_ERROR(mLogger, "Error! Empty message");
    }
    else
    {
        std::string clientName = std::string(data, dataSize);

        pthread_mutex_lock(&mClientsMapMutex);

        tClientsMap::iterator iter = mClientIdMap.begin();
        for (; iter != mClientIdMap.end(); iter ++)
        {
            if (iter->second == clientName)
            {
                LOG4CPLUS_ERROR(mLogger, "Error! Duplicate clients: " + clientName);
                mClientIdMap.erase(iter);
                mSockets->destroySocketForClient(clientName);
                break;
            }
        }
        mClientCounter ++;
        mClientIdMap[mClientCounter] = clientName;
        mSockets->createSocketForClient(mClientIdMap[mClientCounter], CONNECT);

        LOG4CPLUS_INFO(mLogger, "Client name: " + clientName);
        LOG4CPLUS_INFO(mLogger, "Client name: client id: " << mClientCounter);
        pushHelloResponse(mClientCounter);

        pthread_mutex_unlock(&mClientsMapMutex);

        if (mListener)
        {
            mListener->onClientConnected(clientName);
        }
        else
        {
            LOG4CPLUS_ERROR(mLogger, "Error! No listener");
        }
    }
}

void ZmqServer::pushHelloResponse(const int clientId)
{
    ZmqClientServerMessage msg;
    msg.isControlMessage = true;
    msg.clientID = clientId;
    mSockets->sendMessageToClient(mClientIdMap[clientId], sizeof(ZmqClientServerMessage), (const char*)&msg);
}


bool ZmqServer::destroySocketOfClient(std::string const& clientName)
{
    pthread_mutex_lock(&mClientsMapMutex);
    tClientsMap::iterator iter = mClientIdMap.begin();
    for (; iter != mClientIdMap.end(); iter ++)
    {
        if (iter->second == clientName)
        {
            mClientIdMap.erase(iter);
            break;
        }
    }
    pthread_mutex_unlock(&mClientsMapMutex);
    return mSockets->destroySocketForClient(clientName);
}
