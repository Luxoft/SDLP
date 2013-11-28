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


#ifndef PROFILEINSTANCEMANAGER_H
#define PROFILEINSTANCEMANAGER_H

#include <queue>
#include <map>
#include <string>
#include <semaphore.h>
#include <pthread.h>

#include "Logger.hpp"

#include "ProfileManager/ProfileManagerCommon.h"
#include "ProfileManager/ProfileManagerResult.h"
#include "JSONHandler/SDLRPCMessage.h"
#include "ProfileManager/ProfileCommunicator.h"

/**
  *\namespace NsProfileManager
  *\brief Namespace for SmartDeviceLink ProfileManager related functionality.
*/
namespace NsProfileManager
{

class ProfileManager;
class ActiveProfilesRegister;
class ProfileConnectionsRegister;

/**
 * @brief The ProfileInstanceManager class provides profile processes managing functionality and
 * messaging between ProfileManager and profiles.
 */
class ProfileInstanceManager : public NsUtils::IServerListener
{
public:
    ProfileInstanceManager();
    virtual ~ProfileInstanceManager();

    void setProfileManager(ProfileManager *profileManager);
    /**
     * @brief loadProfile Start profile process and load profile
     * @param name Profile name
     * @param appId Application id
     */
    ProfileManagerResult loadProfile(const std::string & name, const int appId);

    /**
     * @brief unloadProfile Unload profile and finish profile process
     * @param name Profile name
     * @param appId Application id
     */
    ProfileManagerResult unloadProfile(const std::string & name, const int appId);

    /**
     * @brief sendAppToProfileMessage Send message received from mobile application to profile
     * @param appId Application id
     * @param profileName Profile name
     * @param data Pointer to data array
     * @param dataSize Data array size
     */
    ProfileManagerResult sendAppToProfileMessage(const int appId,
                                 const std::string & profileName,
                                 const char * data,
                                 const int dataSize);

    /**
     * @brief appStateChanged Send application state changed notification to profile
     * @param profileName Profile name
     * @param state Mobile application state
     * @param appId Application id
     */
    ProfileManagerResult appStateChanged(const std::string & profileName,
                         const MobileAppState state,
                         const int appId);


    bool isProfileActive(const std::string & profileName);

    /**
     * @brief redirectHmiMessageToProfile Send message to a profile that has communicated with this appId
     * @param appId Application id
     * @param message
     * @return false if there is no active profile instance to receive the message; true otherwise
     */
    bool redirectHmiMessageToProfile(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * message);
    
    void redirectAppManHmiMessageToProfile(std::string const& profileName, std::string const& serializedForm);

    void onMobileAppExited(const int appId);


    void onMessageReceived(unsigned int dataSize, char const * const data,
            const std::string &clientName);
    void onClientConnected(const std::string &clientName);

private:
    void handleMessage(ZmqMessageHeader header, const char * data, 
        std::string const& profileName);
    void onChildExited(pid_t pid);
    static void childHandler(int sig);

    void handleProfileToAppMessageBroadcast(std::string const& profileName, const ZmqMessageHeader msg, const char * data);
    void handleProfileStateChangedBroadcast(std::string const& profileName, const ZmqMessageHeader msg);

private:
    ProfileManager *mProfileManager;

    ActiveProfilesRegister * mActiveProfiles;
    ProfileCommunicator * mCommunicator;
    ProfileConnectionsRegister * mProfileConnections;

    std::string mPathToProfiles;
    static Logger mLogger;
};

} //NsProfileManager

#endif //PROFILEINSTANCEMANAGER_H
