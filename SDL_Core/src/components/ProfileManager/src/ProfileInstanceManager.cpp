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


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <fstream>

#include "ProfileManagerUtils/RpcParser.h"

#include "ProfileManager/ProfileInstanceManager.h"
#include "ProfileManager/ProfileManager.h"
#include "ProfileManager/ActiveProfilesRegister.h"
#include "ProfileManager/ProfileConnectionsRegister.h"
#include "ProfileManager/ProfileLibrariesManager.h"

using namespace NsProfileManager;
using namespace NsSmartDeviceLinkRPC;

static ProfileInstanceManager * pimInstance = NULL;

Logger ProfileInstanceManager::mLogger = Logger::getInstance("SDL.ProfileManager.ProfileInstanceManager");

ProfileInstanceManager::ProfileInstanceManager()
    : mProfileManager(NULL),
      mActiveProfiles(new ActiveProfilesRegister()),
      mProfileConnections(new ProfileConnectionsRegister())
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    std::ifstream configFile("profiles.config");
    configFile >> mPathToProfiles;

    mCommunicator = new ProfileCommunicator(this);

    pimInstance = this; // TODO singleton would be better

    static bool first = true;
    if (first)
    {
        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = childHandler;
        sigaction(SIGCHLD, &sa, NULL);
        first = false;
    }
}

ProfileInstanceManager::~ProfileInstanceManager()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (pimInstance == this)
    {
        pimInstance = NULL;
    }

    delete mCommunicator;
    delete mActiveProfiles;
    delete mProfileConnections;
}


void ProfileInstanceManager::childHandler(int sig)
{
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (pimInstance)
        {
            pimInstance->onChildExited(pid);
        }
    }
}

void ProfileInstanceManager::onChildExited(pid_t pid)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    LOG4CPLUS_INFO(mLogger, "child exited with pid: " << pid);
    std::string profileName = mActiveProfiles->getProfileByPID(pid);
    if (profileName != "")
    {
        LOG4CPLUS_INFO(mLogger, "Profile exited: " + profileName);
        mCommunicator->destroySocketOfClient(profileName);
        mActiveProfiles->eraseProfileRecord(profileName);
        std::set<int> connections = mProfileConnections->getProfileConnections(profileName);
        for (std::set<int>::iterator iter = connections.begin(); iter != connections.end(); iter ++)
        {
            mProfileManager->profileClosed(profileName, *iter);
        }
        mProfileConnections->eraseProfileConnections(profileName);
    }
}

void ProfileInstanceManager::setProfileManager(ProfileManager *profileManager)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mProfileManager = profileManager;
}

ProfileManagerResult ProfileInstanceManager::loadProfile(const std::string & name, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (!ProfileLibrariesManager::getInstance().hasLibraryForProfile(mPathToProfiles, name))
    {
        LOG4CPLUS_WARN(mLogger, "No library for " + name);
        return ProfileManagerResult(Result::INVALID_ID, "No library for profile: " + name);
    }

    if (mActiveProfiles->isProfileActive(name))
    {
        LOG4CPLUS_WARN(mLogger, "The profile " + name + " has been loaded already!");
        mProfileConnections->addProfileConnection(name, appId);
        return ProfileManagerResult(Result::IN_USE, name + " has been loaded already");
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        LOG4CPLUS_ERROR(mLogger, "fork failure");
        return ProfileManagerResult(Result::GENERIC_ERROR, "Fork failed!");
    }
    else if (pid == 0)
    {
        std::ifstream configFile("profile_process_link");
        std::string path;
        configFile >> path;
        execl(path.c_str(), PROFILE_PROCESS_NAME, name.c_str(), mPathToProfiles.c_str(), (char *)0);
    }
    else
    {
        LOG4CPLUS_INFO(mLogger, "Profile process created");
        mActiveProfiles->addProfileRecord(name, pid);
        mProfileConnections->addProfileConnection(name, appId);
    }
    return ProfileManagerResult(Result::SUCCESS);
}

ProfileManagerResult ProfileInstanceManager::unloadProfile(const std::string & name, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (!mActiveProfiles->isProfileActive(name))
    {
        LOG4CPLUS_WARN(mLogger, "The profile " + name + " has not been loaded!");
        return ProfileManagerResult(Result::INVALID_ID, "Profile is not active");
    }

    mProfileConnections->addProfileConnection(name, appId);

    mCommunicator->sendMessageToProfile(name, appId, MSG_TYPE_UNLOAD_PROFILE,
        0, 0, 0, 0);
    return ProfileManagerResult(Result::SUCCESS);
}

ProfileManagerResult ProfileInstanceManager::sendAppToProfileMessage(const int appId,
                                                     const std::string & profileName,
                                                     const char * data,
                                                     const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (!mActiveProfiles->isProfileActive(profileName))
    {
        LOG4CPLUS_WARN(mLogger, "The profile " + profileName + " has not been loaded!");
        return ProfileManagerResult(Result::INVALID_ID, "Profile is not active");
    }

    mProfileConnections->addProfileConnection(profileName, appId);
    mCommunicator->sendMessageToProfile(profileName, appId, MSG_TYPE_APP_TO_PROFILE_MESSAGE,
        0, 0, dataSize, data);

    return ProfileManagerResult(Result::SUCCESS);
}

ProfileManagerResult ProfileInstanceManager::appStateChanged(const std::string & profileName,
                                             const MobileAppState state,
                                             const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (!mActiveProfiles->isProfileActive(profileName))
    {
        LOG4CPLUS_WARN(mLogger, "The profile " + profileName + " has not been loaded!");
        return ProfileManagerResult(Result::INVALID_ID, "Profile is not active");
    }

    mProfileConnections->addProfileConnection(profileName, appId);

    mCommunicator->sendMessageToProfile(profileName, appId, MSG_TYPE_APP_STATE_CHANGED,
        state, 0, 0, 0);

    return ProfileManagerResult(Result::SUCCESS);
}

bool ProfileInstanceManager::redirectHmiMessageToProfile(const int appId, 
    NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    std::string profileName = mProfileConnections->getProfileNameByAppId(appId);
    if (profileName.empty())
    {
        LOG4CPLUS_WARN(mLogger, "did not find receiver profile");
        return false;
    }
    LOG4CPLUS_WARN(mLogger, "Found profile name: " +  profileName + " for appId " << appId);

    MessageTypes type = MSG_TYPE_INVALID;
    switch (message->getMessageType())
    {
        case NsSmartDeviceLinkRPC::SDLRPCMessage::RESPONSE:
            type = MSG_TYPE_HMI_RESPONSE;
            break;
        case NsSmartDeviceLinkRPC::SDLRPCMessage::NOTIFICATION:
            type = MSG_TYPE_HMI_NOTIFICATION;
            break;
        case NsSmartDeviceLinkRPC::SDLRPCMessage::REQUEST:
        default:
        {
            LOG4CPLUS_WARN(mLogger, "Unknown or invalid message type!");
            return false;
        }
    }
    unsigned char protocolVersion = message->getProtocolVersion();

    SerializedData data = RpcParser::serializeOutgoingMessage(message);
    if (data.dataSize <= 0)
    {
        LOG4CPLUS_ERROR(mLogger, "Could not serialize outgoing message");
        /**
         * the message wasn't actually handled;
         * but if the protocol version used by profile was different from
         * mobile app, then mobile app may crash if we let the message pass to it
         */
        return true;
    }

    mCommunicator->sendMessageToProfile(profileName, appId, type,
        0, protocolVersion, data.dataSize, data.data);
    delete[] data.data;
    return true;
}

void ProfileInstanceManager::redirectAppManHmiMessageToProfile(std::string const& profileName,
    std::string const& serializedForm)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (!mActiveProfiles->isProfileActive(profileName))
    {
        LOG4CPLUS_WARN(mLogger, "Profile is not active " + profileName);
        return;
    }
    mCommunicator->sendMessageToProfile(profileName, 0, MSG_TYPE_HMI_NOTIFICATION_IVILINK,
        0, 0, serializedForm.size(), serializedForm.c_str());
}

void ProfileInstanceManager::handleMessage(ZmqMessageHeader header, const char * data, 
    std::string const& profileName)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (mProfileManager)
    {
        if (profileName != "")
        {
            switch (header.messageType)
            {
            case MSG_TYPE_PROFILE_STATE_CHANGED:
                mProfileManager->profileStateChanged(profileName,
                                                    (ProfileState) header.state,
                                                    header.appId);
                break;
            case MSG_TYPE_PROFILE_STATE_CHANGED_BROADCAST:
                handleProfileStateChangedBroadcast(profileName, header);
                break;
            case MSG_TYPE_PROFILE_TO_APP_MESSAGE:
            LOG4CPLUS_INFO(mLogger, "Message to profile: " + std::string(data, header.dataSize));
                mProfileManager->sendProfileToAppMessage(profileName,
                                                        header.appId,
                                                        data,
                                                        header.dataSize);
                break;
            case MSG_TYPE_PROFILE_TO_APP_MESSAGE_BROADCAST:
                handleProfileToAppMessageBroadcast(profileName, header, data);
                break;
            case MSG_TYPE_HMI_REQUEST:
            {
                unsigned char protocolVersion = header.protocolVersion;
                NsSmartDeviceLinkRPC::SDLRPCMessage* request = NULL;
                if (protocolVersion == 1)
                {
                    request = RpcParser::parseRequestV1(data, header.dataSize);
                }
                else if (protocolVersion == 2)
                {
                    request = RpcParser::parseRequestV2(data, header.dataSize);
                }
                if (request)
                {
                    mProfileManager->profileHmiRequest(profileName, header.appId, request);
                }
                else
                {
                    LOG4CPLUS_WARN(mLogger, "could not parse message: " + std::string());
                }
            }
                break;
            case MSG_TYPE_HMI_REQUEST_IVILINK:
                mProfileManager->profileAppManHmiRequest(data, header.dataSize);
                break;
            default:
                LOG4CPLUS_WARN(mLogger, "Message FROM profile: incorrect type!");
                break;
            }
        }
        else
        {
            LOG4CPLUS_WARN(mLogger, "We haven't profile name for this pid : "
                            + convertIntegerToString(header.pid));
        }
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Error! Profile Manager pointer == NULL!");
    }
} 

bool ProfileInstanceManager::isProfileActive(const std::string & profileName)
{
    return mActiveProfiles->isProfileActive(profileName);
}

void ProfileInstanceManager::onMobileAppExited(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    std::set<std::string> profilesToNotify = mProfileConnections->eraseAppConnections(appId);
    std::set<std::string>::iterator profileIter = profilesToNotify.begin();
    for (; profileIter != profilesToNotify.end(); profileIter ++)
    {
        mCommunicator->sendMessageToProfile(*profileIter, appId, MSG_TYPE_MOBILE_APP_EXITED,
            0, 0, 0, 0);
    }
}

void ProfileInstanceManager::handleProfileToAppMessageBroadcast(std::string const& profileName, const ZmqMessageHeader msg, const char * data)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    std::set<int> connections = mProfileConnections->getProfileConnections(profileName);
    for (std::set<int>::iterator iter = connections.begin(); iter != connections.end(); iter ++)
    {
        mProfileManager->sendProfileToAppMessage(profileName,
                                                *iter,
                                                data,
                                                msg.dataSize);
    }
}

void ProfileInstanceManager::handleProfileStateChangedBroadcast(std::string const& profileName, const ZmqMessageHeader header)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    std::set<int> connections = mProfileConnections->getProfileConnections(profileName);
    for (std::set<int>::iterator iter = connections.begin(); iter != connections.end(); iter ++)
    {
        mProfileManager->profileStateChanged(profileName,
                                            (ProfileState) header.state,
                                            *iter);
    }
}

void ProfileInstanceManager::onMessageReceived(unsigned int dataSize, char const * const data,
            const std::string &clientName)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (dataSize < sizeof(ZmqMessageHeader))
    {
        LOG4CPLUS_ERROR(mLogger, "Message is too small");
        return;
    }
    ZmqMessageHeader * messageHeader = reinterpret_cast<ZmqMessageHeader*>((char*)data);
    if (dataSize < sizeof(ZmqMessageHeader) + messageHeader->dataSize)
    {
        LOG4CPLUS_ERROR(mLogger, "Message is inconsistent");
        return;
    }
    const char * messageData = data + sizeof(ZmqMessageHeader);
    handleMessage(*messageHeader, messageData, clientName);
}

void ProfileInstanceManager::onClientConnected(const std::string &clientName)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    LOG4CPLUS_INFO(mLogger, "Sending load profile request to : " + clientName);
    std::set<int> connections = mProfileConnections->getProfileConnections(clientName);
    if (connections.empty())
    {
        LOG4CPLUS_ERROR(mLogger, "No connections with profile: " + clientName);
        return;
    }
    mCommunicator->sendMessageToProfile(clientName, *(connections.begin()), MSG_TYPE_LOAD_PROFILE,
        0, 0, 0, 0);
}
