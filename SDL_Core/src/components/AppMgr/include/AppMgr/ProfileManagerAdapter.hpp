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

 
#ifndef PROFILEMANAGERGRADAPTER_HPP_
#define PROFILEMANAGERGRADAPTER_HPP_

#include <string>

#include "Logger.hpp"
#include "ProfileManager/IProfileCallbacks.h"
#include "ProfileManager/ProfileManagerResult.h"

namespace NsProfileManager
{
class ProfileManager;
}

namespace NsSmartDeviceLinkRPC
{
class MobileAppState;
}

namespace NsSmartDeviceLinkRPCV2
{
class MobileAppState;
}

namespace NsAppManager
{

class MobileHandler;

class ProfileManagerAdapter : public NsProfileManager::IProfileCallbacks
{
public:
    ProfileManagerAdapter();
    virtual ~ProfileManagerAdapter();

    /**
     * @brief loadProfile Load profile
     * @param name Profile name
     * @param appId Application id
     * @return INVALID_ID, SUCCESS, REJECTED
     */
    ProfileManagerResult loadProfile(const std::string &profileName, int appId);

    /**
     * @brief unloadProfile Unload profile
     * @param name Profile name
     * @param appId Application id
     * @return INVALID_ID, SUCCESS, REJECTED
     */
    ProfileManagerResult unloadProfile(const std::string &profileName, int appId);

    /**
     * @brief sendAppToProfileMessage Send message received from mobile application to profile
     * @param appId Application id
     * @param profileName Profile name
     * @param data Pointer to data array
     * @param dataSize Data array size
     * @return INVALID_ID, SUCCESS, REJECTED
     */
    ProfileManagerResult sendAppToProfileMessage(const int appId, const std::string & profileName,
            const char * data, const int dataSize);

    /**
     * @brief addProfile Add new profile to the system
     * @param profileName Profile name
     * @param profileBin Pointer to profile binary array
     * @param profileSize Size of profile binary array
     * @param appId Application id
     */
    ProfileManagerResult addProfile(const std::string & profileName,
            const char * profileBin,
            const int profileSize,
            const int appId);

    /**
     * @brief removeProfile Remove profile from system
     * @param profileName Profile name
     * @param appId Application id
     */
    ProfileManagerResult removeProfile(const std::string &profileName, const int appId);

    /**
     * @brief appStateChanged Send application state changed notification to profile
     * @param profileName Profile name
     * @param state Mobile application state
     * @param appId Application id
     * @return INVALID_ID, SUCCESS, REJECTED
     */
    ProfileManagerResult appStateChanged(const std::string &profileName, const int appId,
            NsSmartDeviceLinkRPC::MobileAppState state);

    void onApplicationDisconnected(const int appId);

    /**
     * @brief setProfileManager sets profile manager
     * @param profileMgr pointer on instance of profile manager
     */
    void setProfileManager(NsProfileManager::ProfileManager * profileMgr);

    /**
     * @brief May send the message from HMI to an application with appId to a profile 
     * (that has communicated with this appId before) instead
     * @return true if the message has been sent to a profile instance; false otherwise
     */
    bool redirectHmiMessageToProfile(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * message);

private:
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
                                         const int dataSize);

    /**
     * @brief profileStateChanged Send notification about changes in the profile state
     * @param profileName Profile name
     * @param state New profile state
     * @param appId Application id
     */
    virtual void profileStateChanged(const std::string & profileName,
                                     const NsProfileManager::ProfileState state,
                                     const int appId);

    /**
     * @brief profileClosed Send notification about profile closing
     * @param profileName Profile name
     * @param appId Application id
     */
    virtual void profileClosed(const std::string & profileName, const int appId);

    /**
     * @brief Pass request from a profile instance to AppMgrCore
     */
    virtual void profileHmiRequest(const std::string& profileName, const int appId, 
        NsSmartDeviceLinkRPC::SDLRPCMessage * request) ;

private:
    NsProfileManager::ProfileManager * mProfileManager;
    MobileHandler * mMobileHandler;

    static Logger mLogger;
};

} /* namespace NsAppManager */
#endif /* PROFILEMANAGERGRADAPTER_HPP_ */
