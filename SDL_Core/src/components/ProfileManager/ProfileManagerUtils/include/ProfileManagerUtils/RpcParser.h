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

#ifndef __RPC_PARSER_H__
#define __RPC_PARSER_H__

#include "ProfileManager/RpcHmiAPI.h"
#include "ProfileManager/RpcHmiAPI2.h"

namespace NsProfileManager
{

struct  SerializedData
{
    int dataSize;
    char * data;

    SerializedData()
    {
        dataSize = 0;
        data = NULL;
    }
};

class RpcParser
{
public:

    static bool isIviLinkMessage(NsSmartDeviceLinkRPC::SDLRPCMessage * message);
    
    static NsSmartDeviceLinkRPC::SDLRPCNotification* parseNotificationV1(const char * data, const int dataSize);
    static NsSmartDeviceLinkRPC::SDLRPCMessage* parseNotificationV2(const char * data, const int dataSize);

    static NsSmartDeviceLinkRPC::SDLRPCResponse* parseResponseV1(const char * data, const int dataSize);
    static NsSmartDeviceLinkRPC::SDLRPCResponse* parseResponseV2(const char * data, const int dataSize);

    static NsSmartDeviceLinkRPC::SDLRPCRequest* parseRequestV1(const char * data, const int dataSize);
    static NsSmartDeviceLinkRPC::SDLRPCMessage* parseRequestV2(const char * data, const int dataSize);

    static SerializedData serializeOutgoingMessage(NsSmartDeviceLinkRPC::SDLRPCMessage * message);

private:
    static NsSmartDeviceLinkRPC::SDLRPCMessage * parseMessageV2(const char * data, const int dataSize);
    static SerializedData serializeMessageV2(NsSmartDeviceLinkRPC::SDLRPCMessage * message);

    static bool additionalIntializationV2Requests(NsSmartDeviceLinkRPC::SDLRPCMessage * message);

};

}

#endif //__RPC_PARSER_H__
