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
 *  File:   ZmqSocketCommon.h
 *
 *  Author: Vyacheslav Plachkov
 */


#ifndef ZMQSOCKETCOMMON_H
#define ZMQSOCKETCOMMON_H

#include <unistd.h>
#include <stdint.h>
#include <string>

/**
  *\namespace NsUtils
  *\brief Namespace for iviLink utils
*/
namespace NsUtils
{

typedef std::pair<uint32_t, const char*> tSizedMessage;

static const int32_t UNKNOWN_CLIENT_ID = 0;

// Reply for 0MQ messages
static const char * MSG_REPLY_OK = "OK";
static const char * ZMQ_SOCKET_DIR = "/tmp/ivilinkzmq/";
static const std::string ZMQ_PROTOCOL_PREFIX = std::string("ipc:///tmp/ivilinkzmq/");

/**
 * @brief The ZmqSocketMessage struct is used for the message exchange through the 0MQ sockets
 */
struct ZmqClientServerMessage
{
    ZmqClientServerMessage()
        : isControlMessage(false)
        , clientID(UNKNOWN_CLIENT_ID)
        , dataSize(0)
    {
    }

    bool isControlMessage;
    int32_t clientID;
    uint32_t dataSize;
}__attribute__((packed));

} //NsUtils

#endif //ZMQSOCKETCOMMON_H
