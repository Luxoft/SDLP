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

#include "ProfileManager/IviLinkHmiRequest.h"
#include "ProfileManager/RpcHmiAPI.h"

using namespace NsProfileManager;
using namespace NsSmartDeviceLinkRPC;

IviLinkHmiRequest::IviLinkHmiRequest(void)
    : SDLRPCRequest(1, Marshaller::METHOD_PROFILEREQUESTTOHMI)
    , mDataPayloadSize(0)
    , mDataPayload(NULL)
{
}

IviLinkHmiRequest::IviLinkHmiRequest(std::string const& profile, 
                      std::string const& app, 
                      const char * data, 
                      const int dataSize)
    : SDLRPCRequest(1, Marshaller::METHOD_PROFILEREQUESTTOHMI)
    , mDataPayloadSize(0)
    , mDataPayload(NULL)
    , mProfileName(profile)
    , mDestinationApp(app)
{
    setDataPayload(data, dataSize);
}

IviLinkHmiRequest::~IviLinkHmiRequest(void)
{
    if (mDataPayload)
    {
        delete mDataPayload;
    }
}

bool IviLinkHmiRequest::checkIntegrity(void)
{
    return mDataPayload != NULL && mDataPayloadSize != 0
      && !mProfileName.empty() && !mDestinationApp.empty();
}

unsigned int IviLinkHmiRequest::getDataPayloadSize()
{
    return mDataPayloadSize;
}

const char * IviLinkHmiRequest::getDataPayload()
{
    return mDataPayload;
}

std::string IviLinkHmiRequest::getProfileName()
{
    return mProfileName;
}

std::string IviLinkHmiRequest::getApplicationName()
{
    return mDestinationApp;
}

void IviLinkHmiRequest::setDataPayload(const char * data, unsigned int size)
{
    if (mDataPayload != NULL)
    {
        delete[] mDataPayload;
    }
    mDataPayloadSize = size;
    mDataPayload = new char[size];
    memcpy(mDataPayload, data, size);
}

void IviLinkHmiRequest::setProfileName(std::string const& name)
{
    mProfileName = name;
}

void IviLinkHmiRequest::setApplicationName(std::string const& app)
{
    mDestinationApp = app;
}
