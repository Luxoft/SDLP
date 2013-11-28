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

#include <zmq.h>
#include "ProfileManager/ApplicationManagerHmiCommunicator.h"
#include "ApplicationManagerHmiProtocol/AppManHmiIpcAddress.h"
#include "ApplicationManagerHmiProtocol/ProfilesAppsMessage.h"

using namespace NsProfileManager;
using namespace NsUtils;
using namespace NsSmartDeviceLinkRPC;


ApplicationManagerHmiCommunicator::ApplicationManagerHmiCommunicator(ProfileInstanceManager * pim)
    : mPIM(pim)
{
    mContext = zmq_ctx_new();
    mSenderSocket = new SenderZmqSocket(mContext, TO_APPMAN, BIND); // TODO change depending on startup order
    mReceiverSocket = new ReceiverZmqSocket(mContext, FROM_APPMAN, BIND, this);
}

ApplicationManagerHmiCommunicator::~ApplicationManagerHmiCommunicator()
{
    delete mSenderSocket;
    delete mReceiverSocket;
    zmq_ctx_destroy(mContext);
}

void ApplicationManagerHmiCommunicator::sendMessageToAppManager(const char * data, const unsigned int dataSize)
{
    mSenderSocket->pushMessageToQueue(dataSize, data);
}

void ApplicationManagerHmiCommunicator::handleMessage(tSizedMessage message)
{
    std::string serialized(message.second, message.first);
    ProfilesAppsMessage parsedMessage(serialized);
    if (parsedMessage.isComplete())
    {
        mPIM->redirectAppManHmiMessageToProfile(parsedMessage.getProfileName(), serialized);
    }
}
