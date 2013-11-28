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

/**
 * HMI RPC APIs available for profiles.
 */
 
#ifndef __RPC_HMI_API_H__
#define __RPC_HMI_API_H__

#include "JSONHandler/SDLRPCRequest.h"
#include "JSONHandler/SDLRPCResponse.h"
#include "JSONHandler/SDLRPCMessage.h"
#include "JSONHandler/SDLRPCNotification.h"
#include "JSONHandler/SDLRPCObjects/V1/Marshaller.h"

#include "JSONHandler/SDLRPCObjects/V1/ActionPerformer.h"
#include "JSONHandler/SDLRPCObjects/V1/AddCommand_request.h"
#include "JSONHandler/SDLRPCObjects/V1/AddCommand_response.h"
#include "JSONHandler/SDLRPCObjects/V1/AddSubMenu_request.h"
#include "JSONHandler/SDLRPCObjects/V1/AddSubMenu_response.h"
#include "JSONHandler/SDLRPCObjects/V1/Alert_request.h"
#include "JSONHandler/SDLRPCObjects/V1/Alert_response.h"
#include "JSONHandler/SDLRPCObjects/V1/AppInterfaceUnregisteredReason.h"
#include "JSONHandler/SDLRPCObjects/V1/AudioCaptureQuality.h"
#include "JSONHandler/SDLRPCObjects/V1/AudioStreamingState.h"
#include "JSONHandler/SDLRPCObjects/V1/ButtonCapabilities.h"
#include "JSONHandler/SDLRPCObjects/V1/ButtonEventMode.h"
#include "JSONHandler/SDLRPCObjects/V1/ButtonName.h"
#include "JSONHandler/SDLRPCObjects/V1/ButtonPressMode.h"
#include "JSONHandler/SDLRPCObjects/V1/CharacterSet.h"
#include "JSONHandler/SDLRPCObjects/V1/Choice.h"
#include "JSONHandler/SDLRPCObjects/V1/CreateInteractionChoiceSet_request.h"
#include "JSONHandler/SDLRPCObjects/V1/CreateInteractionChoiceSet_response.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteCommand_request.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteCommand_response.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteInteractionChoiceSet_request.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteInteractionChoiceSet_response.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteSubMenu_request.h"
#include "JSONHandler/SDLRPCObjects/V1/DeleteSubMenu_response.h"
#include "JSONHandler/SDLRPCObjects/V1/DisplayCapabilities.h"
#include "JSONHandler/SDLRPCObjects/V1/DisplayType.h"
#include "JSONHandler/SDLRPCObjects/V1/DriverDistractionState.h"
#include "JSONHandler/SDLRPCObjects/V1/EncodedSyncPData_request.h"
#include "JSONHandler/SDLRPCObjects/V1/EncodedSyncPData_response.h"
#include "JSONHandler/SDLRPCObjects/V1/GenericResponse_response.h"
#include "JSONHandler/SDLRPCObjects/V1/GlobalProperty.h"
#include "JSONHandler/SDLRPCObjects/V1/HMILevel.h"
#include "JSONHandler/SDLRPCObjects/V1/HmiZoneCapabilities.h"
#include "JSONHandler/SDLRPCObjects/V1/InteractionMode.h"
#include "JSONHandler/SDLRPCObjects/V1/Language.h"
#include "JSONHandler/SDLRPCObjects/V1/MediaClockFormat.h"
#include "JSONHandler/SDLRPCObjects/V1/MenuParams.h"
#include "JSONHandler/SDLRPCObjects/V1/OnAppInterfaceUnregistered.h"
#include "JSONHandler/SDLRPCObjects/V1/OnButtonEvent.h"
#include "JSONHandler/SDLRPCObjects/V1/OnButtonPress.h"
#include "JSONHandler/SDLRPCObjects/V1/OnCommand.h"
#include "JSONHandler/SDLRPCObjects/V1/OnDriverDistraction.h"
#include "JSONHandler/SDLRPCObjects/V1/OnEncodedSyncPData.h"
#include "JSONHandler/SDLRPCObjects/V1/OnHMIStatus.h"
#include "JSONHandler/SDLRPCObjects/V1/OnTBTClientState.h"
#include "JSONHandler/SDLRPCObjects/V1/PerformInteraction_request.h"
#include "JSONHandler/SDLRPCObjects/V1/PerformInteraction_response.h"
#include "JSONHandler/SDLRPCObjects/V1/RegisterAppInterface_request.h"
#include "JSONHandler/SDLRPCObjects/V1/RegisterAppInterface_response.h"
#include "JSONHandler/SDLRPCObjects/V1/ResetGlobalProperties_request.h"
#include "JSONHandler/SDLRPCObjects/V1/ResetGlobalProperties_response.h"
#include "JSONHandler/SDLRPCObjects/V1/Result.h"
#include "JSONHandler/SDLRPCObjects/V1/SetGlobalProperties_request.h"
#include "JSONHandler/SDLRPCObjects/V1/SetGlobalProperties_response.h"
#include "JSONHandler/SDLRPCObjects/V1/SetMediaClockTimer_request.h"
#include "JSONHandler/SDLRPCObjects/V1/SetMediaClockTimer_response.h"
#include "JSONHandler/SDLRPCObjects/V1/Show_request.h"
#include "JSONHandler/SDLRPCObjects/V1/Show_response.h"
#include "JSONHandler/SDLRPCObjects/V1/Speak_request.h"
#include "JSONHandler/SDLRPCObjects/V1/Speak_response.h"
#include "JSONHandler/SDLRPCObjects/V1/SpeechCapabilities.h"
#include "JSONHandler/SDLRPCObjects/V1/StartTime.h"
#include "JSONHandler/SDLRPCObjects/V1/SubscribeButton_request.h"
#include "JSONHandler/SDLRPCObjects/V1/SubscribeButton_response.h"
#include "JSONHandler/SDLRPCObjects/V1/SyncMsgVersion.h"
#include "JSONHandler/SDLRPCObjects/V1/SystemContext.h"
#include "JSONHandler/SDLRPCObjects/V1/TBTState.h"
#include "JSONHandler/SDLRPCObjects/V1/TextAlignment.h"
#include "JSONHandler/SDLRPCObjects/V1/TextField.h"
#include "JSONHandler/SDLRPCObjects/V1/TextFieldName.h"
#include "JSONHandler/SDLRPCObjects/V1/TriggerSource.h"
#include "JSONHandler/SDLRPCObjects/V1/TTSChunk.h"
#include "JSONHandler/SDLRPCObjects/V1/UnregisterAppInterface_request.h"
#include "JSONHandler/SDLRPCObjects/V1/UnregisterAppInterface_response.h"
#include "JSONHandler/SDLRPCObjects/V1/UnsubscribeButton_request.h"
#include "JSONHandler/SDLRPCObjects/V1/UnsubscribeButton_response.h"
#include "JSONHandler/SDLRPCObjects/V1/UpdateMode.h"
#include "JSONHandler/SDLRPCObjects/V1/VrCapabilities.h"


#include "ProfileManager/IviLinkHmiRequest.h"
#include "ProfileManager/OnIviLinkHmiNotification.h"

#endif //__RPC_HMI_API_H__
