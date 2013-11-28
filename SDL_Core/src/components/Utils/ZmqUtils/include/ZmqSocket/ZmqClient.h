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
 *  File:   ZmqClient.h
 *
 *  Author: Vyacheslav Plachkov
 */


#ifndef ZMQCLIENT_H
#define ZMQCLIENT_H

#include "Logger.hpp"

#include "ZmqSocket/SenderZmqSocket.h"
#include "ZmqSocket/ReceiverZmqSocket.h"

/**
  *\namespace NsUtils
  *\brief Namespace for utils
*/
namespace NsUtils
{

class IClientListener
{
public:
    virtual ~IClientListener() {}

    /**
     * Invoked when the socket receives a correct message.
     * A response is sent automatically.
     * Data payload is deallocated after this callback, 
     * so it should be copied if you intend to keep it for later use.
     */
    virtual void onMessageReceived(char const * const data, unsigned int dataSize) = 0;

    /**
     * Established connection with server
     */
    virtual void onConnectionEstablished() = 0;
};

class ZmqClient : public IReceiverSocketListener
{

public:
    /**
     * @param clientName is unique text-digit string, client-name
     */
    ZmqClient(const std::string &clientName, const std::string& serverName,
            IClientListener * listener);

    ~ZmqClient();

    void pushMessageToQueue(const unsigned int dataSize, const char * data);

private:
    virtual void handleMessage(tSizedMessage message);
    void pushHelloRequest();

    std::string mClientName;
    std::string mServerName;
    std::string mClientAddress;
    std::string mServerAddress;
    volatile int mClientId;

    void *mZmqContext;
    SenderZmqSocket * mSenderSocket;
    ReceiverZmqSocket * mReceiverSocket;
    IClientListener * mListener;

    static Logger mLogger;
};

} //NsUtils

#endif //ZMQCLIENT_H
