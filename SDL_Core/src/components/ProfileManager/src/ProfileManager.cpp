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


#include <arpa/inet.h>

#include "ProfileManager/ProfileManager.h"
#include "Utils/Base64Coder.h"
#include "ProfileManager/ProfileLibrariesManager.h"
#include "ProfileManager/ProfileInstanceManager.h"
#include "ProfileManager/ApplicationManagerHmiCommunicator.h"

#include "Utils/WorkWithOS.h"
#include "JSONHandler/SDLRPCObjects/V1/Marshaller.h"

using namespace NsProfileManager;
using namespace NsSmartDeviceLinkRPC;

Logger ProfileManager::mLogger = Logger::getInstance(
        LOG4CPLUS_TEXT("SDL.ProfileManager.ProfileManager"));

ProfileManager::ProfileManager(const std::string & pathToProfiles)
	: mProfileManagerAdapter(NULL)
    , mPathToProfiles(pathToProfiles)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mProfileInstanceManager = new ProfileInstanceManager();
    mProfileInstanceManager->setProfileManager(this);
    mAppManCommunicator = new ApplicationManagerHmiCommunicator(mProfileInstanceManager);
}

ProfileManager::~ProfileManager()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    delete mAppManCommunicator;
    delete mProfileInstanceManager;
}

ProfileManagerResult ProfileManager::loadProfile(const std::string & name, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    return mProfileInstanceManager->loadProfile(name, appId);
}

ProfileManagerResult ProfileManager::unloadProfile(const std::string & name, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    return mProfileInstanceManager->unloadProfile(name, appId);
}

ProfileManagerResult ProfileManager::sendAppToProfileMessage(const int appId,
                                             const std::string & profileName,
                                             const char * data,
                                             const int dataSize)
{
    int decodedDataSize = 0;
    char * decodedData = Base64Coder::decode(data, dataSize, decodedDataSize);
    ProfileManagerResult result = mProfileInstanceManager->sendAppToProfileMessage(appId, profileName, 
        decodedData, decodedDataSize);
    delete[] decodedData;
    return result;
}

ProfileManagerResult ProfileManager::addProfile(const std::string & profileName,
                                const char * profileBin,
                                const int profileSize,
                                const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mProfileInstanceManager->isProfileActive(profileName))
    {
        LOG4CPLUS_WARN(mLogger, "Profile " + profileName + " is active, cannot add");
        return ProfileManagerResult(Result::IN_USE, "Profile " + profileName + " is currently active");
    }

    int decodedProfileBinSize = 0;
    const char * decodedProfileBin = Base64Coder::decode(profileBin, profileSize, decodedProfileBinSize);   

    int numberOfAllFrames = 0;
    int currentFrame = 0;
    int offset = 0;

    memcpy(&numberOfAllFrames, decodedProfileBin, sizeof(int32_t));
    numberOfAllFrames = ntohl(numberOfAllFrames);
    offset += sizeof(int32_t);

    memcpy(&currentFrame, decodedProfileBin + offset, sizeof(int32_t));
    currentFrame = ntohl(currentFrame);
    offset += sizeof(int32_t);

    ProfileManagerResult retval = ProfileLibrariesManager::getInstance().appendProfileData(profileName, mPathToProfiles, 
        decodedProfileBin + offset, decodedProfileBinSize - offset, currentFrame, numberOfAllFrames, 
        appId);

    delete[] decodedProfileBin;
    return retval;
}

ProfileManagerResult ProfileManager::removeProfile(const std::string & profileName, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (!mProfileInstanceManager->isProfileActive(profileName))
    {
        return ProfileLibrariesManager::getInstance().eraseLibraryForProfile(mPathToProfiles, profileName);
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "Profile " + profileName + " is active!");
        return ProfileManagerResult(Result::IN_USE, "Profile " + profileName + " is currently active");
    }
}

void ProfileManager::onMobileAppExited(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    ProfileLibrariesManager::getInstance().removeIncompleteDataFromApp(appId, mPathToProfiles);
    mProfileInstanceManager->onMobileAppExited(appId);
}

ProfileManagerResult ProfileManager::appStateChanged(const std::string & profileName,
                                     const MobileAppState state,
                                     const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    return mProfileInstanceManager->appStateChanged(profileName, state, appId);
}

/*
 * From IProfileCallbacks
 */

void ProfileManager::sendProfileToAppMessage(const std::string &profileName,
                                             const int appId,
                                             const char * data,
                                             const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    int encodedDataSize = 0;
    char * encodedData = Base64Coder::encode(data, dataSize, encodedDataSize);
    
	if (mProfileManagerAdapter)
	{
		mProfileManagerAdapter->sendProfileToAppMessage(profileName, appId, encodedData, encodedDataSize);
	}
    delete[] encodedData;
}

void ProfileManager::profileStateChanged(const std::string & profileName,
                                         const ProfileState state,
                                         const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    
	if (mProfileManagerAdapter)
	{
		mProfileManagerAdapter->profileStateChanged(profileName, state, appId);
	}
    else
    {
        LOG4CPLUS_WARN(mLogger, "No profile manager adapter");
    }
}

void ProfileManager::profileClosed(const std::string & profileName, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    
	if (mProfileManagerAdapter)
	{
		mProfileManagerAdapter->profileClosed(profileName, appId);
	}
    else
    {
        LOG4CPLUS_WARN(mLogger, "No profile manager adapter");
    }
}

void ProfileManager::profileHmiRequest(const std::string& profileName, const int appId, 
    NsSmartDeviceLinkRPC::SDLRPCMessage * request)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mProfileManagerAdapter)
    {
        if (!isProfileManagerMessage(request))
        {
            mProfileManagerAdapter->profileHmiRequest(profileName, appId, request);
        }
        else
        {
            LOG4CPLUS_WARN(mLogger, "profileHmiRequest:: request is profile management-related, filtering it out");
            delete request;
        }
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "No profile manager adapter!");
        delete request;
    }
}

void ProfileManager::profileAppManHmiRequest(const char * data, const unsigned int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mAppManCommunicator->sendMessageToAppManager(data, dataSize);
}

bool ProfileManager::redirectHmiMessageToProfile(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (isProfileManagerMessage(message))
    {
        LOG4CPLUS_WARN(mLogger, "Message " << message->getMethodId() << " is one of profile management related");
        return false;
    }
    return mProfileInstanceManager->redirectHmiMessageToProfile(appId, message);
}

bool ProfileManager::isProfileManagerMessage(const NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    int id = message->getMethodId();
    if (message->getProtocolVersion() == 1)
    {
        return id >= NsSmartDeviceLinkRPC::Marshaller::METHOD_LOADPROFILE_REQUEST 
            && id <= NsSmartDeviceLinkRPC::Marshaller::METHOD_ONPROFILESTATECHANGED;
    }
    // TODO protocol version 2 when it is ready
    return false;
}

void ProfileManager::setProfileManagerAdapter(IProfileCallbacks * profileMgrAdapter)
{
	mProfileManagerAdapter = profileMgrAdapter;
}

