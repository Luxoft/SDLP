//
// Copyright (c) 2013, Ford Motor Company
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following
// disclaimer in the documentation and/or other materials provided with the
// distribution.
//
// Neither the name of the Ford Motor Company nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef NSSMARTDEVICELINKKRPC_MARSHALLER_INCLUDE
#define NSSMARTDEVICELINKKRPC_MARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../src/SDLRPCObjectsImpl/V1/RegisterAppInterface_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/RegisterAppInterface_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnregisterAppInterface_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnregisterAppInterface_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SetGlobalProperties_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SetGlobalProperties_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/ResetGlobalProperties_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/ResetGlobalProperties_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddCommand_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddCommand_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteCommand_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteCommand_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddSubMenu_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddSubMenu_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteSubMenu_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteSubMenu_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/CreateInteractionChoiceSet_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/CreateInteractionChoiceSet_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/PerformInteraction_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/PerformInteraction_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteInteractionChoiceSet_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/DeleteInteractionChoiceSet_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Alert_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Alert_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Show_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Show_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Speak_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/Speak_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SetMediaClockTimer_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SetMediaClockTimer_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/EncodedSyncPData_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/EncodedSyncPData_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SubscribeButton_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SubscribeButton_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnsubscribeButton_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnsubscribeButton_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/GenericResponse_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/LoadProfile_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/LoadProfile_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnloadProfile_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/UnloadProfile_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SendAppToProfileMessage_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/SendAppToProfileMessage_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddProfile_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AddProfile_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/RemoveProfile_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/RemoveProfile_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AppStateChanged_requestMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/AppStateChanged_responseMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnHMIStatusMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnAppInterfaceUnregisteredMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnButtonEventMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnButtonPressMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnCommandMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnEncodedSyncPDataMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnTBTClientStateMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnDriverDistractionMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnProfileToAppMessageMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnProfileUnloadedMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V1/OnProfileStateChangedMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPC
{
  class Marshaller
  {
  public:

    enum Methods
    {
      METHOD_INVALID=-1,
      METHOD_REGISTERAPPINTERFACE_REQUEST=0,
      METHOD_REGISTERAPPINTERFACE_RESPONSE=1,
      METHOD_UNREGISTERAPPINTERFACE_REQUEST=2,
      METHOD_UNREGISTERAPPINTERFACE_RESPONSE=3,
      METHOD_SETGLOBALPROPERTIES_REQUEST=4,
      METHOD_SETGLOBALPROPERTIES_RESPONSE=5,
      METHOD_RESETGLOBALPROPERTIES_REQUEST=6,
      METHOD_RESETGLOBALPROPERTIES_RESPONSE=7,
      METHOD_ADDCOMMAND_REQUEST=8,
      METHOD_ADDCOMMAND_RESPONSE=9,
      METHOD_DELETECOMMAND_REQUEST=10,
      METHOD_DELETECOMMAND_RESPONSE=11,
      METHOD_ADDSUBMENU_REQUEST=12,
      METHOD_ADDSUBMENU_RESPONSE=13,
      METHOD_DELETESUBMENU_REQUEST=14,
      METHOD_DELETESUBMENU_RESPONSE=15,
      METHOD_CREATEINTERACTIONCHOICESET_REQUEST=16,
      METHOD_CREATEINTERACTIONCHOICESET_RESPONSE=17,
      METHOD_PERFORMINTERACTION_REQUEST=18,
      METHOD_PERFORMINTERACTION_RESPONSE=19,
      METHOD_DELETEINTERACTIONCHOICESET_REQUEST=20,
      METHOD_DELETEINTERACTIONCHOICESET_RESPONSE=21,
      METHOD_ALERT_REQUEST=22,
      METHOD_ALERT_RESPONSE=23,
      METHOD_SHOW_REQUEST=24,
      METHOD_SHOW_RESPONSE=25,
      METHOD_SPEAK_REQUEST=26,
      METHOD_SPEAK_RESPONSE=27,
      METHOD_SETMEDIACLOCKTIMER_REQUEST=28,
      METHOD_SETMEDIACLOCKTIMER_RESPONSE=29,
      METHOD_ENCODEDSYNCPDATA_REQUEST=30,
      METHOD_ENCODEDSYNCPDATA_RESPONSE=31,
      METHOD_SUBSCRIBEBUTTON_REQUEST=32,
      METHOD_SUBSCRIBEBUTTON_RESPONSE=33,
      METHOD_UNSUBSCRIBEBUTTON_REQUEST=34,
      METHOD_UNSUBSCRIBEBUTTON_RESPONSE=35,
      METHOD_GENERICRESPONSE_RESPONSE=36,
      METHOD_ONHMISTATUS=37,
      METHOD_ONAPPINTERFACEUNREGISTERED=38,
      METHOD_ONBUTTONEVENT=39,
      METHOD_ONBUTTONPRESS=40,
      METHOD_ONCOMMAND=41,
      METHOD_ONENCODEDSYNCPDATA=42,
      METHOD_ONTBTCLIENTSTATE=43,
      METHOD_ONDRIVERDISTRACTION=44,
      METHOD_LOADPROFILE_REQUEST=45,
      METHOD_LOADPROFILE_RESPONSE=46,
      METHOD_UNLOADPROFILE_REQUEST=47,
      METHOD_UNLOADPROFILE_RESPONSE=48,
      METHOD_SENDAPPTOPROFILEMESSAGE_REQUEST=49,
      METHOD_SENDAPPTOPROFILEMESSAGE_RESPONSE=50,
      METHOD_ADDPROFILE_REQUEST=51,
      METHOD_ADDPROFILE_RESPONSE=52,
      METHOD_REMOVEPROFILE_REQUEST=53,
      METHOD_REMOVEPROFILE_RESPONSE=54,
      METHOD_APPSTATECHANGED_REQUEST=55,
      METHOD_APPSTATECHANGED_RESPONSE=56,
      METHOD_ONPROFILETOAPPMESSAGE=57,
      METHOD_ONPROFILEUNLOADED=58,
      METHOD_ONPROFILESTATECHANGED=59,
      METHOD_PROFILEREQUESTTOHMI = 60,
      METHOD_ONHMIREQUESTTOPROFILE = 61,
    };

    Marshaller()					{}
    ~Marshaller()					{}
    
  
    static SDLRPCMessage* fromString(const std::string&);
    static std::string toString(const SDLRPCMessage* msg);
  
    static SDLRPCMessage* fromJSON(const Json::Value&);
    static Json::Value toJSON(const SDLRPCMessage* msg);

  protected:
// RegisterAppInterface_request
    static bool fromString(const std::string& str, RegisterAppInterface_request& res)
    {
      return mRegisterAppInterface_request.fromString(str, res);
    }

    static std::string toString(const RegisterAppInterface_request& res)
    {
      return mRegisterAppInterface_request.toString(res);
    }

// RegisterAppInterface_response
    static bool fromString(const std::string& str, RegisterAppInterface_response& res)
    {
      return mRegisterAppInterface_response.fromString(str, res);
    }

    static std::string toString(const RegisterAppInterface_response& res)
    {
      return mRegisterAppInterface_response.toString(res);
    }

// UnregisterAppInterface_request
    static bool fromString(const std::string& str, UnregisterAppInterface_request& res)
    {
      return mUnregisterAppInterface_request.fromString(str, res);
    }

    static std::string toString(const UnregisterAppInterface_request& res)
    {
      return mUnregisterAppInterface_request.toString(res);
    }

// UnregisterAppInterface_response
    static bool fromString(const std::string& str, UnregisterAppInterface_response& res)
    {
      return mUnregisterAppInterface_response.fromString(str, res);
    }

    static std::string toString(const UnregisterAppInterface_response& res)
    {
      return mUnregisterAppInterface_response.toString(res);
    }

// SetGlobalProperties_request
    static bool fromString(const std::string& str, SetGlobalProperties_request& res)
    {
      return mSetGlobalProperties_request.fromString(str, res);
    }

    static std::string toString(const SetGlobalProperties_request& res)
    {
      return mSetGlobalProperties_request.toString(res);
    }

// SetGlobalProperties_response
    static bool fromString(const std::string& str, SetGlobalProperties_response& res)
    {
      return mSetGlobalProperties_response.fromString(str, res);
    }

    static std::string toString(const SetGlobalProperties_response& res)
    {
      return mSetGlobalProperties_response.toString(res);
    }

// ResetGlobalProperties_request
    static bool fromString(const std::string& str, ResetGlobalProperties_request& res)
    {
      return mResetGlobalProperties_request.fromString(str, res);
    }

    static std::string toString(const ResetGlobalProperties_request& res)
    {
      return mResetGlobalProperties_request.toString(res);
    }

// ResetGlobalProperties_response
    static bool fromString(const std::string& str, ResetGlobalProperties_response& res)
    {
      return mResetGlobalProperties_response.fromString(str, res);
    }

    static std::string toString(const ResetGlobalProperties_response& res)
    {
      return mResetGlobalProperties_response.toString(res);
    }

// AddCommand_request
    static bool fromString(const std::string& str, AddCommand_request& res)
    {
      return mAddCommand_request.fromString(str, res);
    }

    static std::string toString(const AddCommand_request& res)
    {
      return mAddCommand_request.toString(res);
    }

// AddCommand_response
    static bool fromString(const std::string& str, AddCommand_response& res)
    {
      return mAddCommand_response.fromString(str, res);
    }

    static std::string toString(const AddCommand_response& res)
    {
      return mAddCommand_response.toString(res);
    }

// DeleteCommand_request
    static bool fromString(const std::string& str, DeleteCommand_request& res)
    {
      return mDeleteCommand_request.fromString(str, res);
    }

    static std::string toString(const DeleteCommand_request& res)
    {
      return mDeleteCommand_request.toString(res);
    }

// DeleteCommand_response
    static bool fromString(const std::string& str, DeleteCommand_response& res)
    {
      return mDeleteCommand_response.fromString(str, res);
    }

    static std::string toString(const DeleteCommand_response& res)
    {
      return mDeleteCommand_response.toString(res);
    }

// AddSubMenu_request
    static bool fromString(const std::string& str, AddSubMenu_request& res)
    {
      return mAddSubMenu_request.fromString(str, res);
    }

    static std::string toString(const AddSubMenu_request& res)
    {
      return mAddSubMenu_request.toString(res);
    }

// AddSubMenu_response
    static bool fromString(const std::string& str, AddSubMenu_response& res)
    {
      return mAddSubMenu_response.fromString(str, res);
    }

    static std::string toString(const AddSubMenu_response& res)
    {
      return mAddSubMenu_response.toString(res);
    }

// DeleteSubMenu_request
    static bool fromString(const std::string& str, DeleteSubMenu_request& res)
    {
      return mDeleteSubMenu_request.fromString(str, res);
    }

    static std::string toString(const DeleteSubMenu_request& res)
    {
      return mDeleteSubMenu_request.toString(res);
    }

// DeleteSubMenu_response
    static bool fromString(const std::string& str, DeleteSubMenu_response& res)
    {
      return mDeleteSubMenu_response.fromString(str, res);
    }

    static std::string toString(const DeleteSubMenu_response& res)
    {
      return mDeleteSubMenu_response.toString(res);
    }

// CreateInteractionChoiceSet_request
    static bool fromString(const std::string& str, CreateInteractionChoiceSet_request& res)
    {
      return mCreateInteractionChoiceSet_request.fromString(str, res);
    }

    static std::string toString(const CreateInteractionChoiceSet_request& res)
    {
      return mCreateInteractionChoiceSet_request.toString(res);
    }

// CreateInteractionChoiceSet_response
    static bool fromString(const std::string& str, CreateInteractionChoiceSet_response& res)
    {
      return mCreateInteractionChoiceSet_response.fromString(str, res);
    }

    static std::string toString(const CreateInteractionChoiceSet_response& res)
    {
      return mCreateInteractionChoiceSet_response.toString(res);
    }

// PerformInteraction_request
    static bool fromString(const std::string& str, PerformInteraction_request& res)
    {
      return mPerformInteraction_request.fromString(str, res);
    }

    static std::string toString(const PerformInteraction_request& res)
    {
      return mPerformInteraction_request.toString(res);
    }

// PerformInteraction_response
    static bool fromString(const std::string& str, PerformInteraction_response& res)
    {
      return mPerformInteraction_response.fromString(str, res);
    }

    static std::string toString(const PerformInteraction_response& res)
    {
      return mPerformInteraction_response.toString(res);
    }

// DeleteInteractionChoiceSet_request
    static bool fromString(const std::string& str, DeleteInteractionChoiceSet_request& res)
    {
      return mDeleteInteractionChoiceSet_request.fromString(str, res);
    }

    static std::string toString(const DeleteInteractionChoiceSet_request& res)
    {
      return mDeleteInteractionChoiceSet_request.toString(res);
    }

// DeleteInteractionChoiceSet_response
    static bool fromString(const std::string& str, DeleteInteractionChoiceSet_response& res)
    {
      return mDeleteInteractionChoiceSet_response.fromString(str, res);
    }

    static std::string toString(const DeleteInteractionChoiceSet_response& res)
    {
      return mDeleteInteractionChoiceSet_response.toString(res);
    }

// Alert_request
    static bool fromString(const std::string& str, Alert_request& res)
    {
      return mAlert_request.fromString(str, res);
    }

    static std::string toString(const Alert_request& res)
    {
      return mAlert_request.toString(res);
    }

// Alert_response
    static bool fromString(const std::string& str, Alert_response& res)
    {
      return mAlert_response.fromString(str, res);
    }

    static std::string toString(const Alert_response& res)
    {
      return mAlert_response.toString(res);
    }

// Show_request
    static bool fromString(const std::string& str, Show_request& res)
    {
      return mShow_request.fromString(str, res);
    }

    static std::string toString(const Show_request& res)
    {
      return mShow_request.toString(res);
    }

// Show_response
    static bool fromString(const std::string& str, Show_response& res)
    {
      return mShow_response.fromString(str, res);
    }

    static std::string toString(const Show_response& res)
    {
      return mShow_response.toString(res);
    }

// Speak_request
    static bool fromString(const std::string& str, Speak_request& res)
    {
      return mSpeak_request.fromString(str, res);
    }

    static std::string toString(const Speak_request& res)
    {
      return mSpeak_request.toString(res);
    }

// Speak_response
    static bool fromString(const std::string& str, Speak_response& res)
    {
      return mSpeak_response.fromString(str, res);
    }

    static std::string toString(const Speak_response& res)
    {
      return mSpeak_response.toString(res);
    }

// SetMediaClockTimer_request
    static bool fromString(const std::string& str, SetMediaClockTimer_request& res)
    {
      return mSetMediaClockTimer_request.fromString(str, res);
    }

    static std::string toString(const SetMediaClockTimer_request& res)
    {
      return mSetMediaClockTimer_request.toString(res);
    }

// SetMediaClockTimer_response
    static bool fromString(const std::string& str, SetMediaClockTimer_response& res)
    {
      return mSetMediaClockTimer_response.fromString(str, res);
    }

    static std::string toString(const SetMediaClockTimer_response& res)
    {
      return mSetMediaClockTimer_response.toString(res);
    }

// EncodedSyncPData_request
    static bool fromString(const std::string& str, EncodedSyncPData_request& res)
    {
      return mEncodedSyncPData_request.fromString(str, res);
    }

    static std::string toString(const EncodedSyncPData_request& res)
    {
      return mEncodedSyncPData_request.toString(res);
    }

// EncodedSyncPData_response
    static bool fromString(const std::string& str, EncodedSyncPData_response& res)
    {
      return mEncodedSyncPData_response.fromString(str, res);
    }

    static std::string toString(const EncodedSyncPData_response& res)
    {
      return mEncodedSyncPData_response.toString(res);
    }

// SubscribeButton_request
    static bool fromString(const std::string& str, SubscribeButton_request& res)
    {
      return mSubscribeButton_request.fromString(str, res);
    }

    static std::string toString(const SubscribeButton_request& res)
    {
      return mSubscribeButton_request.toString(res);
    }

// SubscribeButton_response
    static bool fromString(const std::string& str, SubscribeButton_response& res)
    {
      return mSubscribeButton_response.fromString(str, res);
    }

    static std::string toString(const SubscribeButton_response& res)
    {
      return mSubscribeButton_response.toString(res);
    }

// UnsubscribeButton_request
    static bool fromString(const std::string& str, UnsubscribeButton_request& res)
    {
      return mUnsubscribeButton_request.fromString(str, res);
    }

    static std::string toString(const UnsubscribeButton_request& res)
    {
      return mUnsubscribeButton_request.toString(res);
    }

// UnsubscribeButton_response
    static bool fromString(const std::string& str, UnsubscribeButton_response& res)
    {
      return mUnsubscribeButton_response.fromString(str, res);
    }

    static std::string toString(const UnsubscribeButton_response& res)
    {
      return mUnsubscribeButton_response.toString(res);
    }

// GenericResponse_response
    static bool fromString(const std::string& str, GenericResponse_response& res)
    {
      return mGenericResponse_response.fromString(str, res);
    }

    static std::string toString(const GenericResponse_response& res)
    {
      return mGenericResponse_response.toString(res);
    }

// LoadProfile_request
    static bool fromString(const std::string& str, LoadProfile_request& res)
    {
      return mLoadProfile_request.fromString(str, res);
    }

    static std::string toString(const LoadProfile_request& res)
    {
      return mLoadProfile_request.toString(res);
    }

// LoadProfile_response
    static bool fromString(const std::string& str, LoadProfile_response& res)
    {
      return mLoadProfile_response.fromString(str, res);
    }

    static std::string toString(const LoadProfile_response& res)
    {
      return mLoadProfile_response.toString(res);
    }

// UnloadProfile_request
    static bool fromString(const std::string& str, UnloadProfile_request& res)
    {
      return mUnloadProfile_request.fromString(str, res);
    }

    static std::string toString(const UnloadProfile_request& res)
    {
      return mUnloadProfile_request.toString(res);
    }

// UnloadProfile_response
    static bool fromString(const std::string& str, UnloadProfile_response& res)
    {
      return mUnloadProfile_response.fromString(str, res);
    }

    static std::string toString(const UnloadProfile_response& res)
    {
      return mUnloadProfile_response.toString(res);
    }

// SendAppToProfileMessage_request
    static bool fromString(const std::string& str, SendAppToProfileMessage_request& res)
    {
      return mSendAppToProfileMessage_request.fromString(str, res);
    }

    static std::string toString(const SendAppToProfileMessage_request& res)
    {
      return mSendAppToProfileMessage_request.toString(res);
    }

// SendAppToProfileMessage_response
    static bool fromString(const std::string& str, SendAppToProfileMessage_response& res)
    {
      return mSendAppToProfileMessage_response.fromString(str, res);
    }

    static std::string toString(const SendAppToProfileMessage_response& res)
    {
      return mSendAppToProfileMessage_response.toString(res);
    }

// AddProfile_request
    static bool fromString(const std::string& str, AddProfile_request& res)
    {
      return mAddProfile_request.fromString(str, res);
    }

    static std::string toString(const AddProfile_request& res)
    {
      return mAddProfile_request.toString(res);
    }

// AddProfile_response
    static bool fromString(const std::string& str, AddProfile_response& res)
    {
      return mAddProfile_response.fromString(str, res);
    }

    static std::string toString(const AddProfile_response& res)
    {
      return mAddProfile_response.toString(res);
    }

// RemoveProfile_request
    static bool fromString(const std::string& str, RemoveProfile_request& res)
    {
      return mRemoveProfile_request.fromString(str, res);
    }

    static std::string toString(const RemoveProfile_request& res)
    {
      return mRemoveProfile_request.toString(res);
    }

// RemoveProfile_response
    static bool fromString(const std::string& str, RemoveProfile_response& res)
    {
      return mRemoveProfile_response.fromString(str, res);
    }

    static std::string toString(const RemoveProfile_response& res)
    {
      return mRemoveProfile_response.toString(res);
    }

// AppStateChanged_request
    static bool fromString(const std::string& str, AppStateChanged_request& res)
    {
      return mAppStateChanged_request.fromString(str, res);
    }

    static std::string toString(const AppStateChanged_request& res)
    {
      return mAppStateChanged_request.toString(res);
    }

// AppStateChanged_response
    static bool fromString(const std::string& str, AppStateChanged_response& res)
    {
      return mAppStateChanged_response.fromString(str, res);
    }

    static std::string toString(const AppStateChanged_response& res)
    {
      return mAppStateChanged_response.toString(res);
    }

// OnHMIStatus
    static bool fromString(const std::string& str, OnHMIStatus& res)
    {
      return mOnHMIStatus.fromString(str, res);
    }

    static std::string toString(const OnHMIStatus& res)
    {
      return mOnHMIStatus.toString(res);
    }

// OnAppInterfaceUnregistered
    static bool fromString(const std::string& str, OnAppInterfaceUnregistered& res)
    {
      return mOnAppInterfaceUnregistered.fromString(str, res);
    }

    static std::string toString(const OnAppInterfaceUnregistered& res)
    {
      return mOnAppInterfaceUnregistered.toString(res);
    }

// OnButtonEvent
    static bool fromString(const std::string& str, OnButtonEvent& res)
    {
      return mOnButtonEvent.fromString(str, res);
    }

    static std::string toString(const OnButtonEvent& res)
    {
      return mOnButtonEvent.toString(res);
    }

// OnButtonPress
    static bool fromString(const std::string& str, OnButtonPress& res)
    {
      return mOnButtonPress.fromString(str, res);
    }

    static std::string toString(const OnButtonPress& res)
    {
      return mOnButtonPress.toString(res);
    }

// OnCommand
    static bool fromString(const std::string& str, OnCommand& res)
    {
      return mOnCommand.fromString(str, res);
    }

    static std::string toString(const OnCommand& res)
    {
      return mOnCommand.toString(res);
    }

// OnEncodedSyncPData
    static bool fromString(const std::string& str, OnEncodedSyncPData& res)
    {
      return mOnEncodedSyncPData.fromString(str, res);
    }

    static std::string toString(const OnEncodedSyncPData& res)
    {
      return mOnEncodedSyncPData.toString(res);
    }

// OnTBTClientState
    static bool fromString(const std::string& str, OnTBTClientState& res)
    {
      return mOnTBTClientState.fromString(str, res);
    }

    static std::string toString(const OnTBTClientState& res)
    {
      return mOnTBTClientState.toString(res);
    }

// OnDriverDistraction
    static bool fromString(const std::string& str, OnDriverDistraction& res)
    {
      return mOnDriverDistraction.fromString(str, res);
    }

    static std::string toString(const OnDriverDistraction& res)
    {
      return mOnDriverDistraction.toString(res);
    }

// OnProfileToAppMessage
    static bool fromString(const std::string& str, OnProfileToAppMessage& res)
    {
      return mOnProfileToAppMessage.fromString(str, res);
    }

    static std::string toString(const OnProfileToAppMessage& res)
    {
      return mOnProfileToAppMessage.toString(res);
    }

// OnProfileUnloaded
    static bool fromString(const std::string& str, OnProfileUnloaded& res)
    {
      return mOnProfileUnloaded.fromString(str, res);
    }

    static std::string toString(const OnProfileUnloaded& res)
    {
      return mOnProfileUnloaded.toString(res);
    }

// OnProfileStateChanged
    static bool fromString(const std::string& str, OnProfileStateChanged& res)
    {
      return mOnProfileStateChanged.fromString(str, res);
    }

    static std::string toString(const OnProfileStateChanged& res)
    {
      return mOnProfileStateChanged.toString(res);
    }

    struct localHash
    {
      const char *name;
      unsigned int idx;
      void* marshaller;					// Bingo!!!  old good plain C with direct casting!!!
    };
  
  private:

    static RegisterAppInterface_requestMarshaller mRegisterAppInterface_request;
    static RegisterAppInterface_responseMarshaller mRegisterAppInterface_response;
    static UnregisterAppInterface_requestMarshaller mUnregisterAppInterface_request;
    static UnregisterAppInterface_responseMarshaller mUnregisterAppInterface_response;
    static SetGlobalProperties_requestMarshaller mSetGlobalProperties_request;
    static SetGlobalProperties_responseMarshaller mSetGlobalProperties_response;
    static ResetGlobalProperties_requestMarshaller mResetGlobalProperties_request;
    static ResetGlobalProperties_responseMarshaller mResetGlobalProperties_response;
    static AddCommand_requestMarshaller mAddCommand_request;
    static AddCommand_responseMarshaller mAddCommand_response;
    static DeleteCommand_requestMarshaller mDeleteCommand_request;
    static DeleteCommand_responseMarshaller mDeleteCommand_response;
    static AddSubMenu_requestMarshaller mAddSubMenu_request;
    static AddSubMenu_responseMarshaller mAddSubMenu_response;
    static DeleteSubMenu_requestMarshaller mDeleteSubMenu_request;
    static DeleteSubMenu_responseMarshaller mDeleteSubMenu_response;
    static CreateInteractionChoiceSet_requestMarshaller mCreateInteractionChoiceSet_request;
    static CreateInteractionChoiceSet_responseMarshaller mCreateInteractionChoiceSet_response;
    static PerformInteraction_requestMarshaller mPerformInteraction_request;
    static PerformInteraction_responseMarshaller mPerformInteraction_response;
    static DeleteInteractionChoiceSet_requestMarshaller mDeleteInteractionChoiceSet_request;
    static DeleteInteractionChoiceSet_responseMarshaller mDeleteInteractionChoiceSet_response;
    static Alert_requestMarshaller mAlert_request;
    static Alert_responseMarshaller mAlert_response;
    static Show_requestMarshaller mShow_request;
    static Show_responseMarshaller mShow_response;
    static Speak_requestMarshaller mSpeak_request;
    static Speak_responseMarshaller mSpeak_response;
    static SetMediaClockTimer_requestMarshaller mSetMediaClockTimer_request;
    static SetMediaClockTimer_responseMarshaller mSetMediaClockTimer_response;
    static EncodedSyncPData_requestMarshaller mEncodedSyncPData_request;
    static EncodedSyncPData_responseMarshaller mEncodedSyncPData_response;
    static SubscribeButton_requestMarshaller mSubscribeButton_request;
    static SubscribeButton_responseMarshaller mSubscribeButton_response;
    static UnsubscribeButton_requestMarshaller mUnsubscribeButton_request;
    static UnsubscribeButton_responseMarshaller mUnsubscribeButton_response;
    static GenericResponse_responseMarshaller mGenericResponse_response;
    static LoadProfile_requestMarshaller mLoadProfile_request;
    static LoadProfile_responseMarshaller mLoadProfile_response;
    static UnloadProfile_requestMarshaller mUnloadProfile_request;
    static UnloadProfile_responseMarshaller mUnloadProfile_response;
    static SendAppToProfileMessage_requestMarshaller mSendAppToProfileMessage_request;
    static SendAppToProfileMessage_responseMarshaller mSendAppToProfileMessage_response;
    static AddProfile_requestMarshaller mAddProfile_request;
    static AddProfile_responseMarshaller mAddProfile_response;
    static RemoveProfile_requestMarshaller mRemoveProfile_request;
    static RemoveProfile_responseMarshaller mRemoveProfile_response;
    static AppStateChanged_requestMarshaller mAppStateChanged_request;
    static AppStateChanged_responseMarshaller mAppStateChanged_response;
    static OnHMIStatusMarshaller mOnHMIStatus;
    static OnAppInterfaceUnregisteredMarshaller mOnAppInterfaceUnregistered;
    static OnButtonEventMarshaller mOnButtonEvent;
    static OnButtonPressMarshaller mOnButtonPress;
    static OnCommandMarshaller mOnCommand;
    static OnEncodedSyncPDataMarshaller mOnEncodedSyncPData;
    static OnTBTClientStateMarshaller mOnTBTClientState;
    static OnDriverDistractionMarshaller mOnDriverDistraction;
    static OnProfileToAppMessageMarshaller mOnProfileToAppMessage;
    static OnProfileUnloadedMarshaller mOnProfileUnloaded;
    static OnProfileStateChangedMarshaller mOnProfileStateChanged;

    static const char* getName(Methods e)
    {
       return (e>=0 && e<60) ? mHashTable[e].name : NULL;
    }
     
    static const Methods getIndex(const char* s);
  
    static const localHash mHashTable[60];
    
    friend class Marshaller_intHash;
  };

}

#endif
