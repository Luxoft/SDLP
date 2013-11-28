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
 

#include "AppMgr/ProfileManagerAdapter.hpp"
#include "AppMgr/MobileHandler.h"
#include "AppMgr/AppMgrCore.h"
#include "JSONHandler/SDLRPCObjects/V1/Marshaller.h"
#include "JSONHandler/SDLRPCObjects/V2/Marshaller.h"
#include "ProfileManager/ProfileManager.h"

using namespace NsSmartDeviceLinkRPCV2;

namespace NsAppManager
{

Logger ProfileManagerAdapter::mLogger = Logger::getInstance("SDL.ProfileManager.ProfileManagerAdapter");

ProfileManagerAdapter::ProfileManagerAdapter()
    : mProfileManager(NULL)
    , mMobileHandler(&MobileHandler::getInstance())
{
}

ProfileManagerAdapter::~ProfileManagerAdapter()
{
}

void ProfileManagerAdapter::setProfileManager(NsProfileManager::ProfileManager * profileMgr)
{
    mProfileManager = profileMgr;
}

ProfileManagerResult ProfileManagerAdapter::loadProfile(const std::string &profileName, int appId)
{
    if (mProfileManager)
    {
        return mProfileManager->loadProfile(profileName, appId);
    }
    LOG4CPLUS_WARN(mLogger, "Profile manager is not available");
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
}

ProfileManagerResult ProfileManagerAdapter::unloadProfile(const std::string &profileName, int appId)
{
    if (mProfileManager)
    {
        return mProfileManager->unloadProfile(profileName, appId);
    }
    LOG4CPLUS_WARN(mLogger, "Profile manager is not available");
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
}

ProfileManagerResult ProfileManagerAdapter::sendAppToProfileMessage(const int appId, 
        const std::string & profileName, const char * data, const int dataSize)
{
    if (mProfileManager)
    {
        return mProfileManager->sendAppToProfileMessage(appId, profileName, data, dataSize);
    }
    LOG4CPLUS_WARN(mLogger, "Profile manager is not available");
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
}

ProfileManagerResult ProfileManagerAdapter::addProfile(const std::string & profileName,
        const char * profileBin,
        const int profileSize,
        const int appId)
{
    if (mProfileManager)
    {
        return mProfileManager->addProfile(profileName, profileBin, profileSize, appId);
    }
    LOG4CPLUS_WARN(mLogger, "Profile manager is not available");
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
}

ProfileManagerResult ProfileManagerAdapter::removeProfile(const std::string &profileName, 
        const int appId)
{
    if (mProfileManager)
    {
        return mProfileManager->removeProfile(profileName, appId);
    }
    LOG4CPLUS_WARN(mLogger, "Profile manager is not available");
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
}

ProfileManagerResult ProfileManagerAdapter::appStateChanged(const std::string &profileName, 
        const int appId, NsSmartDeviceLinkRPC::MobileAppState state)
{
    if (mProfileManager && NsSmartDeviceLinkRPC::MobileAppState::INVALID_ENUM != state.get())
    {
        NsProfileManager::MobileAppState tState;
        switch (state.get())
        {
        case NsSmartDeviceLinkRPC::MobileAppState::INVALID_ENUM:
            return NsSmartDeviceLinkRPC::Result::REJECTED;
            break;
        case NsSmartDeviceLinkRPC::MobileAppState::MOBILE_APP_FOREGROUND:
            tState = NsProfileManager::MobileAppState::MOBILE_APP_FOREGROUND;
            break;
        case NsSmartDeviceLinkRPC::MobileAppState::MOBILE_APP_BACKGROUND:
            tState = NsProfileManager::MobileAppState::MOBILE_APP_BACKGROUND;
            break;
        case NsSmartDeviceLinkRPC::MobileAppState::MOBILE_APP_LOCK_SCREEN:
            tState = NsProfileManager::MobileAppState::MOBILE_APP_LOCK_SCREEN;
            break;
        }
        return mProfileManager->appStateChanged(profileName, tState, appId);
    }
    if (!mProfileManager)
    {
        return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::REJECTED);
    }
    return ProfileManagerResult(NsSmartDeviceLinkRPC::Result::INVALID_DATA, 
        "Invalid state of mobile app!");
}

void ProfileManagerAdapter::onApplicationDisconnected(const int appId)
{
    LOG4CPLUS_WARN(mLogger, "Connection lost with: " << appId);
    mProfileManager->onMobileAppExited(appId);
}

void ProfileManagerAdapter::sendProfileToAppMessage(const std::string & profileName,
                                     const int appId,
                                     const char * data,
                                     const int dataSize)
{
    if (!mMobileHandler)
    {
        LOG4CPLUS_WARN(mLogger, "Mobile handler is not available");
    }
    else if (!data)
    {
        LOG4CPLUS_WARN(mLogger, "Does not have data");
    }
    else
    {
        NsSmartDeviceLinkRPC::OnProfileToAppMessage * message = 
            new NsSmartDeviceLinkRPC::OnProfileToAppMessage();
        std::string dataString(data, dataSize);
        message->set_data(dataString);
        message->set_name(profileName);
        mMobileHandler->sendRPCMessage(message, appId);
    }
}

void ProfileManagerAdapter::profileStateChanged(const std::string & profileName,
                                 const NsProfileManager::ProfileState state,
                                 const int appId)
{
    if (mMobileHandler)
    {
        NsSmartDeviceLinkRPC::OnProfileStateChanged * message = 
            new NsSmartDeviceLinkRPC::OnProfileStateChanged;
        NsSmartDeviceLinkRPC::ProfileState tState;
        switch(state)
        {
        case NsProfileManager::ProfileState::PROFILE_STATE_FOREGROUND:
            tState = NsSmartDeviceLinkRPC::ProfileState::FOREGROUND;
            break;
        case NsProfileManager::ProfileState::PROFILE_STATE_BACKGROUND:
            tState = NsSmartDeviceLinkRPC::ProfileState::BACKGROUND;
            break;
        case NsProfileManager::ProfileState::PROFILE_STATE_LIMITED:
            tState = NsSmartDeviceLinkRPC::ProfileState::LIMITED;
            break;
        }
        message->set_state(tState);
        message->set_name(profileName);
        mMobileHandler->sendRPCMessage(message, appId);
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "Mobile handler is not available");
    }
}

void ProfileManagerAdapter::profileClosed(const std::string & profileName, const int appId)
{
    if (mMobileHandler)
    {
        NsSmartDeviceLinkRPC::OnProfileUnloaded * message = 
            new NsSmartDeviceLinkRPC::OnProfileUnloaded();
        message->set_name(profileName);
        mMobileHandler->sendRPCMessage(message, appId);
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "Mobile handler is not available");
    }
}

void ProfileManagerAdapter::profileHmiRequest(const std::string& profileName, const int appId, 
    NsSmartDeviceLinkRPC::SDLRPCMessage * request) 
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    AppMgrCore::getInstance().pushMobileRPCMessage(request, appId);
}

bool ProfileManagerAdapter::redirectHmiMessageToProfile(const int appId, 
    NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mProfileManager)
    {
        bool result = mProfileManager->redirectHmiMessageToProfile(appId, message);
        if (!result)
        {
            int messageVersion = message->getProtocolVersion();
            Application* app = AppMgrCore::getInstance().getItem(appId);
            if (!app)
            {
                LOG4CPLUS_WARN(mLogger, "Could not retrieve app to check for version match: " 
                    << messageVersion);
                return false;
            }
            int appVersion = app->getProtocolVersion();
            if (appVersion != messageVersion)
            {
                LOG4CPLUS_INFO(mLogger, "App version: " << appVersion << 
                    " message version: " << messageVersion);
                LOG4CPLUS_INFO(mLogger, "Saving mobile app from critical error!");
                // mobile app may fail if it expects protocol 1 and receives protocol 2 instead
                return true;
            }
            else
            {
                // ok to pass this message to mobile app
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

} /* namespace NsAppManager */
