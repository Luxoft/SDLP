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


#include <dlfcn.h>
#include <cassert>
#include <iostream>
#include <cstring>
#include <zmq.h>

#include "ProfileProcess/ProfileProcess.h"
#include "ProfileManagerUtils/RpcParser.h"
#include "ProfileManager/OnIviLinkHmiNotification.h"
#include "ApplicationManagerHmiProtocol/ProfilesAppsMessage.h"

using namespace NsProfileManager;

Logger ProfileProcess::mLogger =
            Logger::getInstance(LOG4CPLUS_TEXT("SDL.ProfileManager.ProfileProcess"));

#define LOG4CPLUS_ERROR_WITH_ERRNO(logger, message) LOG4CPLUS_ERROR(logger, message << ", error code " << errno << " (" << strerror(errno) << ")")

ProfileProcess::ProfileProcess(const std::string &profileName, const std::string &pathToProfiles)
    : mProfileImpl(NULL),
      mCreateProfileFunc(NULL),
      mDestroyProfileFunc(NULL),
      mProfileName(profileName),
      mPathToProfiles(pathToProfiles)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    mSender = new ProfileManagerCommunicator(mProfileName, this);
    sem_init(&mStopSema, 0, 0);
    mainLoop();
}

ProfileProcess::~ProfileProcess()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    delete mSender;
}

void ProfileProcess::mainLoop()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    sem_wait(&mStopSema);
}

void ProfileProcess::loadProfile(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    std::string path = mPathToProfiles + "lib" + mProfileName + ".so";

    LOG4CPLUS_INFO(mLogger, "Loading profile: " + path);
    mLibHandle = dlopen(path.c_str(), RTLD_NOW);
    if (!mLibHandle)
    {
        LOG4CPLUS_ERROR(mLogger, "Can't load profile library. dlopen failed");
        LOG4CPLUS_INFO(mLogger, "dlerror: " + std::string(dlerror()));
    }
    assert(mLibHandle);

    mCreateProfileFunc = (CreateProfileFunc *) dlsym(mLibHandle, CREATE_PROFILE_FUNC_NAME);
    assert(mCreateProfileFunc);
    if (!mCreateProfileFunc)
    {
        LOG4CPLUS_ERROR(mLogger, "Can't get CreateProfileFunc from profile library");
        return;
    }

    mDestroyProfileFunc = (DestroyProfileFunc *) dlsym(mLibHandle, DESTROY_PROFILE_FUNC_NAME);
    assert(mDestroyProfileFunc);
    if (!mDestroyProfileFunc)
    {
        LOG4CPLUS_ERROR(mLogger, "Can't get DestroyProfileFunc from profile library");
        return;
    }

    mProfileImpl = mCreateProfileFunc();
    mProfileImpl->setProfileManagerProxy(this);
    mProfileImpl->onLoaded(appId);
    for (tPendingMessagesList::iterator iter = mPendingMessagesList.begin(); iter != mPendingMessagesList.end(); iter ++)
    {
        onMessageReceived(iter->second, iter->first);
        delete[] iter->second;
    }
    mPendingMessagesList.clear();
}

void ProfileProcess::unloadProfile(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (mProfileImpl)
    {
        mProfileImpl->onUnload(appId);
    }
    stopOperations();
}

void ProfileProcess::stopOperations()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (mProfileImpl)
    {
        mDestroyProfileFunc(mProfileImpl);
        mProfileImpl = NULL;
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Profile pointer == 0 (" + mProfileName + ")");
    }

    if (dlclose(mLibHandle) != 0)
    {
        LOG4CPLUS_ERROR(mLogger, "Profile library closing error (Profile : " + mProfileName + ")");
    }

    sem_post(&mStopSema);
}

void ProfileProcess::sendAppToProfileMessage(const int appId,
                                             const std::string &profileName,
                                             const char * data,
                                             const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (mProfileImpl)
    {
        mProfileImpl->onMessageReceived(data, dataSize, appId);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Profile pointer == 0 (" + profileName + ")");
    }
}

void ProfileProcess::appStateChanged(const MobileAppState state, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (mProfileImpl)
    {
        mProfileImpl->onAppStateChanged(state, appId);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Profile pointer == 0");
    }
}

void ProfileProcess::onHmiResponse(const int appId, const char * data, const int dataSize, const unsigned char version)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    NsSmartDeviceLinkRPC::SDLRPCResponse* response = NULL;

    if (version == 1)
    {
        response = RpcParser::parseResponseV1(data, dataSize);
    }
    else if (version == 2)
    {
        response = RpcParser::parseResponseV2(data, dataSize);
    }

    if (response)
    {
        mProfileImpl->onHmiRpcResponse(appId, response);
        delete response;
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "Could not parse response: " + std::string(data, dataSize));
    }
}

void ProfileProcess::onHmiNotification(const int appId, const char * data, const int dataSize, const unsigned char version)
{    
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    NsSmartDeviceLinkRPC::SDLRPCMessage* noti = NULL;
    if (version == 1)
    {
        noti = RpcParser::parseNotificationV1(data, dataSize);
    }
    else if (version == 2)
    {
        noti = RpcParser::parseNotificationV2(data, dataSize);
    }
    if (noti)
    {
        mProfileImpl->onHmiRpcNotification(appId, noti);
        delete noti;
    }
    else
    {
        LOG4CPLUS_WARN(mLogger, "Could not parse notification: " + std::string(data, dataSize));
    }
}

void ProfileProcess::onAppManHmiNotification(const int appId, const char * data, const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    ProfilesAppsMessage message(std::string(data, dataSize));
    OnIviLinkHmiNotification * noti = new OnIviLinkHmiNotification();
    noti->setApplicationName(message.getApplicationName());
    noti->setDataPayload(message.getDataPayload(), message.getDataPayloadSize());
    noti->setProfileName(message.getProfileName());
    if (mProfileImpl)
    {
        mProfileImpl->onHmiRpcNotification(appId, noti);
    }
    delete noti;
}

/*
 * From IProfileCallbacks
 */
void ProfileProcess::sendProfileToAppMessage(const int appId,
                                             const char * data,
                                             const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mSender->pushMessageToQueue(appId, MSG_TYPE_PROFILE_TO_APP_MESSAGE, 
        0, 0, dataSize, data);
}

void ProfileProcess::broadcastProfileToAppMessage(const char * data,
                                                  const int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mSender->pushMessageToQueue(0, MSG_TYPE_PROFILE_TO_APP_MESSAGE_BROADCAST, 
        0, 0, dataSize, data);
}

void ProfileProcess::broadcastProfileStateChanged(const ProfileState state)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mSender->pushMessageToQueue(0, MSG_TYPE_PROFILE_STATE_CHANGED_BROADCAST, 
        state, 0, 0, NULL);
}

void ProfileProcess::profileStateChanged(const ProfileState state,
                                         const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    mSender->pushMessageToQueue(appId, MSG_TYPE_PROFILE_STATE_CHANGED, 
        state, 0, 0, NULL);
}


void ProfileProcess::profileHmiRequest(const int appId, NsSmartDeviceLinkRPC::SDLRPCMessage * request)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (!request)
    {
        LOG4CPLUS_ERROR(mLogger, "Request is null!");
        return;
    }
    if (RpcParser::isIviLinkMessage(request))
    {
        IviLinkHmiRequest * iviMessage = dynamic_cast<IviLinkHmiRequest*>(request);
        if (iviMessage == NULL)
        {
            LOG4CPLUS_ERROR(mLogger, "Incorrect message type");
            return;
        }
        ProfilesAppsMessage msg;
        msg.setProfileName(iviMessage->getProfileName());
        msg.setApplicationName(iviMessage->getApplicationName());
        msg.setDataPayload(iviMessage->getDataPayload(), iviMessage->getDataPayloadSize());
        std::string serializedMessage = msg.serialize();

        mSender->pushMessageToQueue(appId, MSG_TYPE_HMI_REQUEST_IVILINK,
            0, 0, serializedMessage.size(), serializedMessage.c_str());
        return;
    }

    NsSmartDeviceLinkRPC::SDLRPCMessage::MessageType type = request->getMessageType();
    if (request->getProtocolVersion() == 1)
    {
        if (type != NsSmartDeviceLinkRPC::SDLRPCMessage::REQUEST)
        {
            LOG4CPLUS_ERROR(mLogger, "Invalid message type for protocol 1");
            delete request;
            return;
        }
    }
    else if (request->getProtocolVersion() == 2)
    {
        if (type != NsSmartDeviceLinkRPC::SDLRPCMessage::REQUEST 
         && type != NsSmartDeviceLinkRPC::SDLRPCMessage::UNDEFINED)
        {
            LOG4CPLUS_ERROR(mLogger, "Invalid message type for protocol 2");
            delete request;
            return;
        }
    }

    SerializedData data = RpcParser::serializeOutgoingMessage(request);
    unsigned char protocolVersion = request->getProtocolVersion();
    delete request;
    if (data.dataSize <= 0)
    {
        LOG4CPLUS_ERROR(mLogger, "Could not serialize outgoing message");
        return;
    }

    mSender->pushMessageToQueue(appId, MSG_TYPE_HMI_REQUEST, 
        0, protocolVersion, data.dataSize, data.data);
}

void ProfileProcess::profileClosed(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    // profile manager will handle the closing by itself, nothing is sent
    stopOperations();
}

void ProfileProcess::onMessageReceived(char const * const data, unsigned int dataSize)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (dataSize < sizeof(ZmqMessageHeader))
    {
        LOG4CPLUS_ERROR(mLogger, "Message is too small");
        return;
    }
    ZmqMessageHeader * header = reinterpret_cast<ZmqMessageHeader*>((char*) data);
    if (dataSize < header->dataSize + sizeof(ZmqMessageHeader))
    {
        LOG4CPLUS_ERROR(mLogger, "Message is inconsistent");
        return;
    }
    const char * messageData = data + sizeof(ZmqMessageHeader);
    if (!mProfileImpl && header->messageType != MSG_TYPE_LOAD_PROFILE)
    {
        LOG4CPLUS_WARN(mLogger, "no profile instance, storing message for after LOADED");
        char * dataCopy = new char[dataSize];
        memcpy(dataCopy, data, dataSize);
        mPendingMessagesList.push_back(std::make_pair(dataSize, dataCopy));
        return;
    }
    switch (header->messageType)
    {
        case MSG_TYPE_LOAD_PROFILE:
            loadProfile(header->appId);
            break;
        case MSG_TYPE_UNLOAD_PROFILE:
            unloadProfile(header->appId);
            break;
        case MSG_TYPE_APP_STATE_CHANGED:
            appStateChanged((MobileAppState)header->state, header->appId);
            break;
        case MSG_TYPE_APP_TO_PROFILE_MESSAGE:
            sendAppToProfileMessage(header->appId,
                                    mProfileName,
                                    messageData,
                                    header->dataSize);
            break;
        case MSG_TYPE_HMI_RESPONSE:
            onHmiResponse(header->appId, messageData, header->dataSize, header->protocolVersion);
            break;
        case MSG_TYPE_HMI_NOTIFICATION:
            onHmiNotification(header->appId, messageData, header->dataSize, header->protocolVersion);
            break;
        case MSG_TYPE_MOBILE_APP_EXITED:
            if (mProfileImpl)
            {
                mProfileImpl->onMobileAppDisconnected(header->appId);
            }
            break;
        case MSG_TYPE_HMI_NOTIFICATION_IVILINK:
            onAppManHmiNotification(header->appId, messageData, header->dataSize);
            break;
        default:
            LOG4CPLUS_WARN(mLogger, "Message to profile: incorrect type!");
            break;
    }
}

void ProfileProcess::onConnectionEstablished()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
}
