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

#ifndef __PROFILE_SOCKETS_REGISTRY_HPP
#define __PROFILE_SOCKETS_REGISTRY_HPP

#include "ZmqSocket/ZmqServer.h"
#include "ProfileManager/ProfileManagerCommon.h"

namespace NsProfileManager
{
/**
 * ZmqServer that communicates with ProfileProcesses.
 */
class ProfileCommunicator : public NsUtils::ZmqServer
{
public:
    ProfileCommunicator(NsUtils::IServerListener * listener);
    virtual ~ProfileCommunicator() {}
    
    void sendMessageToProfile(std::string const& profileName, const int appId,
    	const MessageTypes type, int state, int protocolVersion,
    	const int dataSize, const char * data);
};

}

#endif // __PROFILE_SOCKETS_REGISTRY_HPP
