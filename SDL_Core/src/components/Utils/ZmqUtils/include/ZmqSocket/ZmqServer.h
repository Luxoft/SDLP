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
 *  File:   ZmqServer.h
 *
 *  Author: Vyacheslav Plachkov
 */


#ifndef ZMQSERVER_H
#define ZMQSERVER_H


#include "Logger.hpp"

#include <pthread.h>
#include "ZmqSocket/ZmqSocketCommon.h"
#include "ZmqSocket/ReceiverZmqSocket.h"

namespace NsUtils
{

class ZmqSocketsRegister;

class IServerListener
{
public:
    virtual ~IServerListener() {}

    /**
     * Invoked when the socket receives a correct message.
     * A response is sent automatically.
     * Data payload of the message (if there is any)
     * is deallocated after this callback, so you should copy it
     * if you intend to keep it for later use.
     */
    virtual void onMessageReceived(unsigned int dataSize, char const * const data,
            const std::string &clientName) = 0;
    /*
     * Informs server listener about new client
     */
    virtual void onClientConnected(const std::string &clientName) = 0;
};

class ZmqServer : public IReceiverSocketListener
{
    typedef std::map<int,std::string> tClientsMap;
public:
    ZmqServer(const std::string &serverName, IServerListener * listener);
    virtual ~ZmqServer();

    bool sendMessageToClient(const std::string & clientName,
                             const char * data, const int dataSize);

    bool destroySocketOfClient(std::string const& clientName);
private:
    void handleMessage(tSizedMessage message);
    void handleHelloRequest(char const * const data, const unsigned int dataSize);
    void pushHelloResponse(const int clientId);

private:

    void *mZmqContext;
    pthread_mutex_t mClientsMapMutex;

    ZmqSocketsRegister * mSockets;
    ReceiverZmqSocket * mReceiverSocket;
    std::string mServerName;
    std::string mServerAddress;
    IServerListener * mListener;
    tClientsMap mClientIdMap;
    int mClientCounter;

    static Logger mLogger;
};

} //NsUtils

#endif //ZMQSERVER_H
