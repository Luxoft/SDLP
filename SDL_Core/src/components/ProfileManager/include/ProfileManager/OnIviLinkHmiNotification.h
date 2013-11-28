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

#ifndef __ON_IVILINK_HMI_NOTIFICATION_H__
#define __ON_IVILINK_HMI_NOTIFICATION_H__
#include <string>

#include "JSONHandler/SDLRPCNotification.h"

namespace NsProfileManager
{

class OnIviLinkHmiNotification : public NsSmartDeviceLinkRPC::SDLRPCNotification
{
public:
    OnIviLinkHmiNotification(void);

    OnIviLinkHmiNotification(std::string const& app, std::string const& profile,
        const char * data, unsigned int dataSize);
    virtual ~OnIviLinkHmiNotification(void);

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

    std::string mDestinationProfileName;
    std::string mSenderApplicationName;
};
}

#endif
