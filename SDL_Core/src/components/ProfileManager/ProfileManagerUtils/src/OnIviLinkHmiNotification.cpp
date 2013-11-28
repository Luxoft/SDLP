/**
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
/**
 * @author Elena Bratanova <ebratanova@luxoft.com>
 */

#include <string.h>

#include "ProfileManager/OnIviLinkHmiNotification.h"
#include "ProfileManager/RpcHmiAPI.h"

using namespace NsProfileManager;
using namespace NsSmartDeviceLinkRPC;

OnIviLinkHmiNotification::OnIviLinkHmiNotification(void)
    : SDLRPCNotification(1, Marshaller::METHOD_ONHMIREQUESTTOPROFILE)
    , mDataPayloadSize(0)
    , mDataPayload(NULL)
{
}

OnIviLinkHmiNotification::OnIviLinkHmiNotification(std::string const& app, std::string const& profile, 
        const char * data, unsigned int dataSize)
    : SDLRPCNotification(1, Marshaller::METHOD_ONHMIREQUESTTOPROFILE)
    , mDataPayloadSize(0)
    , mDataPayload(NULL)
    , mDestinationProfileName(profile)
    , mSenderApplicationName(app)
{
    setDataPayload(data, dataSize);
}

OnIviLinkHmiNotification::~OnIviLinkHmiNotification(void)
{
    if (mDataPayload)
    {
        delete mDataPayload;
    }
}

bool OnIviLinkHmiNotification::checkIntegrity(void)
{
    return mDataPayload != NULL && mDataPayloadSize != 0
        && !mDestinationProfileName.empty() && !mSenderApplicationName.empty();
}

unsigned int OnIviLinkHmiNotification::getDataPayloadSize()
{
    return mDataPayloadSize;
}

const char * OnIviLinkHmiNotification::getDataPayload()
{
    return mDataPayload;
}

std::string OnIviLinkHmiNotification::getProfileName()
{
    return mDestinationProfileName;
}

std::string OnIviLinkHmiNotification::getApplicationName()
{
    return mSenderApplicationName;
}

void OnIviLinkHmiNotification::setDataPayload(const char * data, unsigned int size)
{
    if (mDataPayload != NULL)
    {
        delete[] mDataPayload;
    }
    mDataPayloadSize = size;
    mDataPayload = new char[size];
    memcpy(mDataPayload, data, size);
}

void OnIviLinkHmiNotification::setProfileName(std::string const& name)
{
    mDestinationProfileName = name;
}

void OnIviLinkHmiNotification::setApplicationName(std::string const& app)
{
    mSenderApplicationName = app;
}
