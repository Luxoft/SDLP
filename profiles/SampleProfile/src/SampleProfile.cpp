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
 

#include <iostream>

#include "SampleProfile/SampleProfile.h"
#include "ProfileManager/RpcHmiAPI.h"

using namespace NsProfileManager;
using namespace NsSmartDeviceLinkRPC;

Logger SampleProfile::mLogger = Logger::getInstance("SDL.SampleProfile");

#define RESPONSE "PONG!"

#define HMI_EVENT "Button pressed: "

extern "C" IProfile *CreateProfile()
{
    return new SampleProfile;
}

extern "C" void DestroyProfile(IProfile *profile)
{
    delete profile;
}

SampleProfile::SampleProfile()
    : mCallbacks(NULL),
      mName("SampleProfile")
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
}

void SampleProfile::onLoaded(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    initUi(appId);
    showAlert(appId, "SampleProfile", "Loaded!");
}

SampleProfile::~SampleProfile()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
}

void SampleProfile::onMessageReceived(const char *data, const int dataSize, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    LOG4CPLUS_INFO(mLogger, "Message received : " + std::string(data, dataSize));
    LOG4CPLUS_INFO(mLogger, "Message received : dataSize = " << dataSize);
    LOG4CPLUS_INFO(mLogger, "Message received : appId = " << appId);

    mCallbacks->sendProfileToAppMessage(appId, RESPONSE, sizeof(RESPONSE));
    showAlert(appId, "SampleProfile", "Received: " + std::string(data, dataSize));
}

void SampleProfile::onAppStateChanged(const NsProfileManager::MobileAppState state, const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
}

void SampleProfile::onUnload(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    showAlert(appId, "SampleProfile", "Unloaded!");
}

void SampleProfile::onHmiRpcResponse(const int appId, NsSmartDeviceLinkRPC::SDLRPCResponse * response)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    LOG4CPLUS_INFO(mLogger, "Got response version = " << response->getProtocolVersion());
}

void SampleProfile::initUi(const int appId)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    NsSmartDeviceLinkRPCV2::Show_request * request = new NsSmartDeviceLinkRPCV2::Show_request();
    request->setCorrelationID(200);
    request->set_mainField1("Hello!");
    request->set_mainField2("SampleProfile");
    mCallbacks->profileHmiRequest(appId, request);
    sendBindButton(appId, ButtonName::OK);
    sendBindButton(appId, ButtonName::SEEKLEFT);
    sendBindButton(appId, ButtonName::SEEKRIGHT);
    sendBindButton(appId, ButtonName::TUNEUP);
    sendBindButton(appId, ButtonName::TUNEDOWN);
}

void SampleProfile::onHmiRpcNotification(const int appId, 
    NsSmartDeviceLinkRPC::SDLRPCMessage * notification)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    if (notification->getProtocolVersion() == 2)
    {
        LOG4CPLUS_INFO(mLogger, "Got notification ver. 2!");
        return;
    }

    if (notification->getMethodId() == Marshaller::METHOD_ONHMISTATUS)
    {
        OnHMIStatus * castNoti = (OnHMIStatus*)notification;
        if (castNoti->get_hmiLevel().get() == HMILevel::HMI_FULL)
        {
            initUi(appId);
            mCallbacks->profileStateChanged(NsProfileManager::PROFILE_STATE_FOREGROUND, appId);
        }
        else if (castNoti->get_hmiLevel().get() == HMILevel::HMI_LIMITED)
        {
            mCallbacks->profileStateChanged(NsProfileManager::PROFILE_STATE_LIMITED, appId);
        }
        else
        {
            mCallbacks->profileStateChanged(NsProfileManager::PROFILE_STATE_BACKGROUND, appId);
        }
    }
    else if (notification->getMethodId() == Marshaller::METHOD_ONBUTTONPRESS)
    {
        std::string buttonEvent(HMI_EVENT, sizeof(HMI_EVENT));
        buttonEvent += convertIntegerToString((int)((OnButtonPress*)notification)->get_buttonName().get());
        mCallbacks->sendProfileToAppMessage(appId, buttonEvent.c_str(), buttonEvent.length());
    } 
}

void SampleProfile::setProfileManagerProxy(IProfileManagerProxy *callbacks)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);

    if (callbacks)
    {
        mCallbacks = callbacks;
    }
}

void SampleProfile::showAlert(const int appId, std::string const& line1, 
    std::string const& line2, int duration)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    NsSmartDeviceLinkRPCV2::Alert_request * request = new NsSmartDeviceLinkRPCV2::Alert_request();
    request->setCorrelationID(150);
    request->set_alertText1(line1);
    request->set_alertText2(line2);
    request->set_duration(duration);
    mCallbacks->profileHmiRequest(appId, request);

    NsSmartDeviceLinkRPCV2::ListFiles_request * list = new NsSmartDeviceLinkRPCV2::ListFiles_request();
    mCallbacks->profileHmiRequest(appId, list);
}

void SampleProfile::sendBindButton(const int appId, const int button)
{
    SubscribeButton_request * request = new SubscribeButton_request();
    request->setCorrelationID(150);
    request->set_buttonName(ButtonName((ButtonName::ButtonNameInternal)button));
    mCallbacks->profileHmiRequest(appId, request);
}
