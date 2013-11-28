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
 *  File:   ZmqClient.cpp
 *
 *  Author: Vyacheslav Plachkov
 */


#include <cstring>
#include <zmq.h>

#include "ZmqSocket/ZmqClient.h"

#define SOCKET_LSN_TIMEOUT_MILLIS 1000

using namespace NsUtils;

Logger ZmqClient::mLogger =
            Logger::getInstance(LOG4CPLUS_TEXT("Utils.ZmqSocket.ZmqClient"));

#define LOG4CPLUS_ERROR_WITH_ERRNO(logger, message) LOG4CPLUS_ERROR(logger, message << ", error code " << errno << " (" << strerror(errno) << ")")

ZmqClient::ZmqClient(const std::string &clientName, const std::string& serverName,
        IClientListener * listener)
    : mClientName(clientName)
    , mServerName(serverName)
    , mClientAddress(ZMQ_PROTOCOL_PREFIX + clientName)
    , mServerAddress(ZMQ_PROTOCOL_PREFIX + serverName)
    , mClientId(UNKNOWN_CLIENT_ID)
    , mZmqContext(NULL)
    , mSenderSocket(NULL)
    , mReceiverSocket(NULL)
    , mListener(listener)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    mZmqContext = zmq_ctx_new();

    if (mZmqContext)
    {
        mSenderSocket = new SenderZmqSocket(mZmqContext,mServerAddress, CONNECT);
        pushHelloRequest();
        mReceiverSocket = new ReceiverZmqSocket(mZmqContext, mClientAddress, BIND, this);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Error getting 0MQ context");
        return;
    }
}

ZmqClient::~ZmqClient()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mSenderSocket)
    {
        delete mSenderSocket;
    }
    if (mReceiverSocket)
    {
        delete mReceiverSocket;
    }
    zmq_ctx_destroy(mZmqContext);
}

void ZmqClient::pushMessageToQueue(const unsigned int dataSize, const char * data)
{
    if (mSenderSocket)
    {
        if (mClientId != UNKNOWN_CLIENT_ID)
        {            
            ZmqClientServerMessage msg;
            msg.clientID = mClientId;
            msg.dataSize = dataSize;
            char buffer[sizeof(ZmqClientServerMessage) + dataSize];
            bzero(buffer, sizeof(buffer));
            memcpy(buffer, &msg, sizeof(ZmqClientServerMessage));
            memcpy(buffer + sizeof(ZmqClientServerMessage), data, dataSize);
            mSenderSocket->pushMessageToQueue(sizeof(buffer), buffer);
        }
        else
        {
            LOG4CPLUS_ERROR(mLogger, "ZmqClient::pushMessageToQueue error: unknown id");
        }
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "ZmqClient::pushMessageToQueue error: no sender socket");
    }
}

void ZmqClient::pushHelloRequest()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mSenderSocket)
    {
        ZmqClientServerMessage msg;
        msg.isControlMessage = true;
        msg.clientID = mClientId;
        msg.dataSize = mClientName.length();
        char buffer[sizeof(ZmqClientServerMessage) + msg.dataSize];
        memcpy(buffer, &msg, sizeof(ZmqClientServerMessage));
        memcpy(buffer + sizeof(ZmqClientServerMessage), mClientName.c_str(), msg.dataSize);
        mSenderSocket->pushMessageToQueue(sizeof(buffer), buffer);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "ZmqClient::pushHelloRequest error: no sender socket");
    }
}

void ZmqClient::handleMessage(tSizedMessage message)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (message.first < sizeof(ZmqClientServerMessage))
    {
        LOG4CPLUS_ERROR(mLogger, "Message is too small: " << message.first);
        return;
    }
    ZmqClientServerMessage * cliServMessage = reinterpret_cast<ZmqClientServerMessage*>((char*)message.second);
    const char * data = message.second + sizeof(ZmqClientServerMessage);
    if (message.first < sizeof(ZmqClientServerMessage) + cliServMessage->dataSize)
    {
        LOG4CPLUS_ERROR(mLogger, "message is inconsistent!");
        return;
    }

    if (cliServMessage->isControlMessage)
    {
        mClientId = cliServMessage->clientID;
        LOG4CPLUS_INFO(mLogger, "Client id: " + mClientId);
        if (mListener)
        {
            mListener->onConnectionEstablished();
        }
        else
        {
            LOG4CPLUS_ERROR(mLogger, "Error! 0MQ Client Listener pointer == NULL!");
        }
    }
    else if (mListener)
    {
        mListener->onMessageReceived(data, cliServMessage->dataSize);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Error! 0MQ Client Listener pointer == NULL!");
    }
}
