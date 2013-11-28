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

#ifndef __IVILINK_HMI_REQUEST_HPP__
#define __IVILINK_HMI_REQUEST_HPP__

#include <vector>
#include <string>

#include "JSONHandler/SDLRPCRequest.h"

namespace NsProfileManager
{

class IviLinkHmiRequest : public NsSmartDeviceLinkRPC::SDLRPCRequest
{
public:
    IviLinkHmiRequest(std::string const& profile, 
                      std::string const& app, 
                      const char * data, 
                      const int dataSize);
    IviLinkHmiRequest(void);
    virtual ~IviLinkHmiRequest(void);
    bool checkIntegrity(void);
    unsigned int getDataPayloadSize();
    const char * getDataPayload();
    std::string getProfileName();
    std::string getApplicationName();

    void setDataPayload(const char * data, unsigned int size);
    void setProfileName(std::string const&);
    void setApplicationName(std::string const&);
private:
    unsigned int mDataPayloadSize; 
    char * mDataPayload;
    std::string mProfileName;
    std::string mDestinationApp;
  };
}

#endif //__IVILINK_HMI_REQUEST_HPP__
