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


#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "Logger.hpp"

#include "ProfileManager/IProfileCallbacks.h"
#include "ProfileManager/ProfileManagerResult.h"
/**
  *\namespace NsProfileManager
  *\brief Namespace for SmartDeviceLink ProfileManager related functionality.
*/
namespace NsProfileManager
{

class ProfileInstanceManager;
class ApplicationManagerHmiCommunicator;

/**
 * @brief The ProfileManager class provides profile managing functionality and communication between
 * SDL core and profiles
 */
class ProfileManager : public IProfileCallbacks
{

public:
    ProfileManager(const std::string & pathToProfiles);

    ~ProfileManager();

    /**
     * @brief loadProfile Load profile
     * @param name Profile name
     * @param appId Application id
     * @return true if profile has been loaded (as a result of the call or earlier)
     */
    ProfileManagerResult loadProfile(const std::string & name, const int appId);

    /**
     * @brief unloadProfile Unload profile
     * @param name Profile name
     * @param appId Application id
     * @return false if no profile has been found to unload
     */
    ProfileManagerResult unloadProfile(const std::string & name, const int appId);

    /**
     * @brief sendAppToProfileMessage Send message received from mobile application to profile
     * @param appId Application id
     * @param profileName Profile name
     * @param data Pointer to data array
     * @param dataSize Data array size
     * @return false if no profile with this name is active
     */
    ProfileManagerResult sendAppToProfileMessage(const int appId,
                                 const std::string & profileName,
                                 const char * data,
                                 const int dataSize);

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
    ProfileManagerResult removeProfile(const std::string & profileName, const int appId);

    /**
     * @brief appStateChanged Send application state changed notification to profile
     * @param profileName Profile name
     * @param state Mobile application state
     * @param appId Application id
     * @return false if no profile has been found
     */
    ProfileManagerResult appStateChanged(const std::string & profileName,
                         const MobileAppState state,
                         const int appId);

    void onMobileAppExited(const int appId);

    // From IProfileCallbacks

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
                                     const ProfileState state,
                                     const int appId);

    /**
     * @brief profileClosed Send notification about profile closing
     * @param profileName Profile name
     * @param appId Application id
     */
    virtual void profileClosed(const std::string & profileName, const int appId);

    /**
     * @brief passes Requests from a profile instance to the profile manager adapter
     */
    virtual void profileHmiRequest(const std::string& profileName, const int appId, 
        NsSmartDeviceLinkRPC::SDLRPCMessage * request);
    virtual void profileAppManHmiRequest(const char * data, const unsigned int dataSize);

    /**
     * @brief setProfileManagerAdapter sets pointer on profile manager adapter
     * @param profileMgrAdapter is pointer on base class of of profile manager adapter instance
     */
    void setProfileManagerAdapter(IProfileCallbacks * profileMgrAdapter);

    /**
     * @brief Filters out profile management-related messages, and passes the rest to ProfileInstanceManager
     * @return false if the message is profile management-related; otherwise see ProfileInstanceManager
     */
    bool redirectHmiMessageToProfile(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * message);

private:
    bool isProfileManagerMessage(const NsSmartDeviceLinkRPC::SDLRPCMessage * message);

private:
    ProfileInstanceManager * mProfileInstanceManager;
    ApplicationManagerHmiCommunicator * mAppManCommunicator;
    IProfileCallbacks *mProfileManagerAdapter;
    std::string mPathToProfiles;
    static Logger mLogger;
};

} //NsProfileManager

#endif //PROFILEMANAGER_H
