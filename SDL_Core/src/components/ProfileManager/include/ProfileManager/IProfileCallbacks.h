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


#ifndef IPROFILECALLBACKS_H
#define IPROFILECALLBACKS_H

#include <string>

#include "ProfileManager/ProfileManagerCommon.h"

#include "JSONHandler/SDLRPCRequest.h"

/**
  *\namespace NsProfileManager
  *\brief Namespace for SmartDeviceLink ProfileManager related functionality.
*/
namespace NsProfileManager
{

/**
 * @brief The IProfileCallbacks class is the interface for profile callbacks
 */
class IProfileCallbacks
{

public:
    /**
     * @brief sendProfileToAppMessage Send message from profile to the mobile application
     * @param profileName Profile name
     * @param appId Application id
     * @param data Pointer to the data array
     * @param dataSize Data array size
     */
    virtual void sendProfileToAppMessage(const std::string & profileName,
                                         const int appId,
                                         const char * data,
                                         const int dataSize) = 0;

    /**
     * @brief profileStateChanged Send notification about changes in the profile state
     * @param profileName Profile name
     * @param state New profile state
     * @param appId Application id
     */
    virtual void profileStateChanged(const std::string & profileName,
                                     const ProfileState state,
                                     const int appId) = 0;

    /**
     * @brief profileClosed Send notification about profile closing
     * @param profileName Profile name
     * @param appId Application id
     */
    virtual void profileClosed(const std::string & profileName, const int appId) = 0;

    /**
     * @brief profileHmiRequest send request to the HMI from profile
     * @param profileName Profile name
     * @param appId Application id
     * @param request request to be passed to the HMI
     */
    virtual void profileHmiRequest(const std::string& profileName, const int appId, 
        NsSmartDeviceLinkRPC::SDLRPCMessage * request) = 0;

    virtual ~IProfileCallbacks() {}
};

/**
 * @brief The IProfileManagerProxy class is the interface of Profile Manager for Profile instance
 */
class IProfileManagerProxy
{
public:
    /**
     * @brief sendProfileToAppMessage Send message from profile to the mobile application
     * @param appId Application id
     * @param data Pointer to the data array
     * @param dataSize Data array size
     */
    virtual void sendProfileToAppMessage(const int appId,
                                         const char * data,
                                         const int dataSize) = 0;

    /**
     * @brief broadcastProfileToAppMessage Send message from profile to all mobile applications
     * that have ever communicated with this profile
     * @param data Pointer to the data array
     * @param dataSize Data array size
     */
    virtual void broadcastProfileToAppMessage(const char * data,
                                              const int dataSize) = 0;

    /**
     * @brief broadcastProfileStateChanged Send notification from profile to all mobile applications
     * that have ever communicated with this profile     
     * @param state New profile state
     */
    virtual void broadcastProfileStateChanged(const ProfileState state) = 0;
    
    /**
     * @brief profileStateChanged Send notification about changes in the profile state
     * @param state New profile state
     * @param appId Application id
     */
    virtual void profileStateChanged(const ProfileState state,
                                     const int appId) = 0;

    /**
     * @brief profileClosed Send notification about profile closing
     * @param appId Application id
     */
    virtual void profileClosed(const int appId) = 0;

    /**
     * @brief profileHmiRequest send request to the HMI from profile
     * @param appId Application id
     * @param request request to be passed to the HMI, is deleted inside this method
     */
    virtual void profileHmiRequest(const int appId,  NsSmartDeviceLinkRPC::SDLRPCMessage * request) = 0;

    virtual ~IProfileManagerProxy() {}
};

} //NsProfileManager

#endif //IPROFILECALLBACKS_H
