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


#ifndef __PROFILE_MANAGER_RESULT_H__
#define __PROFILE_MANAGER_RESULT_H__

#include <string>

#include "JSONHandler/SDLRPCObjects/V1/Result.h"

struct ProfileManagerResult
{
    std::string description;
    NsSmartDeviceLinkRPC::Result::ResultInternal retcode;

    ProfileManagerResult(NsSmartDeviceLinkRPC::Result::ResultInternal code)
    {
        retcode = code;
        switch (code)
        {
        case NsSmartDeviceLinkRPC::Result::SUCCESS:
            description = "Request successful";
            break;
        case NsSmartDeviceLinkRPC::Result::INVALID_ID:
            description = "Profile Name is unknown";
            break;
        case NsSmartDeviceLinkRPC::Result::REJECTED:
            description = "No access to profile manager or could not parse request";
            break;
        default:
            description = "Some other error";
        }
    }

    ProfileManagerResult(NsSmartDeviceLinkRPC::Result::ResultInternal code, std::string descr)
    {
        retcode = code;
        description = descr;
    }
};

#endif //__PROFILE_MANAGER_RESULT_H__
