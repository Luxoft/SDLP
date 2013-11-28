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
 

#ifndef TESTSENDINGMSGPROFILE_H
#define TESTSENDINGMSGPROFILE_H

#include "Logger.hpp"

#include "ProfileManager/IProfile.h"

class TestSendingMsgProfile : public NsProfileManager::IProfile
{

public:

    TestSendingMsgProfile();

    ~TestSendingMsgProfile();

    // From IProfile

    /**
     * @brief onMessageReceived Incoming messages handling
     * @param data pointer to data array
     * @param dataSize data array size
     * @param appId Application id
     */
    virtual void onMessageReceived(const char * data, const int dataSize, const int appId);

    /**
     * @brief onAppStateChanged Mobile application state changes handling
     * @param state Mobile application state
     * @param appId Application id
     */
    virtual void onAppStateChanged(const NsProfileManager::MobileAppState state,
                                   const int appId);

    /**
     * @brief onUnloadProfile Unloading profile handling
     * @param appId Application id
     */
    virtual void onUnload(const int appId);

    /**
     * @brief onLoaded - first callback - will be called right after creation with app id 
     * that requested the load. ProfileManagerProxy is set already and can be used.
     * @param appId Application id
     */
    virtual void onLoaded(const int appId);

    /**
     * Called when response from the HMI comes.
     * Pointer to response shouldn't be held onto, as it is deallocated after onHmiRpcResponse
     */
    virtual void onHmiRpcResponse(const int appId, NsSmartDeviceLinkRPC::SDLRPCResponse * response);

    /**
     * Called when a notification from the HMI comes.
     * Pointer to the notification shouldn't be held onto, as it is deallocated after onHmiRpcNotification
     */
    virtual void onHmiRpcNotification(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * notification);

    /**
     * @brief setProfileCallbacks Set profile callbacks
     * @param callbacks Profile callbacks
     */
    virtual void setProfileManagerProxy(NsProfileManager::IProfileManagerProxy * callbacks);

    /**
     * @brief sendNullMsgToApp Sends NULL message to application
     */
    void sendNullMsgToApp();

private:
    NsProfileManager::IProfileManagerProxy * mCallbacks;
    std::string mName;
    static Logger mLogger;
    int mAppId;

};

#endif //TESTSENDINGMSGPROFILE_H
