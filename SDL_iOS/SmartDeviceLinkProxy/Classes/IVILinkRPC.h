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

#ifndef SmartDeviceLinkProxy_IVILinkRPCCalls_h
#define SmartDeviceLinkProxy_IVILinkRPCCalls_h
// enums
#import "iviLink/SDLProfileState.h"
#import "iviLink/SDLMobileAppState.h"
// requests
#import "iviLink/SDLAddProfile.h"
#import "iviLink/SDLLoadProfile.h"
#import "iviLink/SDLAppStateChanged.h"
#import "iviLink/SDLRemoveProfile.h"
#import "iviLink/SDLSendAppToProfileMessage.h"
#import "iviLink/SDLUnloadProfile.h"
// notifications
#import "iviLink/SDLOnProfileToAppMessage.h"
#import "iviLink/SDLOnProfileStateChanged.h"
#import "iviLink/SDLOnProfileUnloaded.h"
// responses
#import "iviLink/SDLAddProfileResponse.h"
#import "iviLink/SDLLoadProfileResponse.h"
#import "iviLink/SDLAppStateChangedResponse.h"
#import "iviLink/SDLRemoveProfileResponse.h"
#import "iviLink/SDLSendAppToProfileMessageResponse.h"
#import "iviLink/SDLUnloadProfileResponse.h"

#import "iviLink/ProfileBinaryPacketizer.h"

#endif
