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


#ifndef __ZMQSOCKETSREGISTER_H__
#define __ZMQSOCKETSREGISTER_H__

#include <pthread.h>
#include <zmq.h>
#include <string>
#include <list>
#include <map>

#include "Logger.hpp"
#include "ZmqSocket/ZmqSocketCommon.h"
#include "ZmqSocket/SocketConnectionType.h"


namespace NsUtils
{

class SenderZmqSocket;
/**
 * \namespace NsUtils
 * \brief Creates and stores zeromq sockets for clients
 */
class ZmqSocketsRegister
{
    typedef std::map<std::string, SenderZmqSocket*> tSocketsMap; 
    typedef std::pair<int, char*> tPendingMessage;
    typedef std::list<tPendingMessage> tPendingMessagesList;
    typedef std::map<std::string,tPendingMessagesList> tPendingMessagesToClientsMap;
public:
    ZmqSocketsRegister(void * zmqContext);
    ~ZmqSocketsRegister();

    bool createSocketForClient(std::string const& clientName, SocketConnectionType type);

    bool destroySocketForClient(std::string const& clientName);

    bool sendMessageToClient(std::string const& clientName,
            const unsigned int dataSize, const char * const data);

private:
    void * mZmqContext;
    tSocketsMap mSockets;
    pthread_mutex_t mSocketsMutex;

    tPendingMessagesToClientsMap mPendingMessages;

    static Logger mLogger;
};

}

#endif //__ZMQSOCKETSREGISTER_HPP__
