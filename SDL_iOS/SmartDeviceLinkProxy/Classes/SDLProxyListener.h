//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "RPC/SDLAddCommandResponse.h"
#import "RPC/SDLAddSubMenuResponse.h"
#import "RPC/SDLEncodedSyncPDataResponse.h"
#import "RPC/SDLAlertResponse.h"
#import "RPC/SDLCreateInteractionChoiceSetResponse.h"
#import "RPC/SDLDeleteCommandResponse.h"
#import "RPC/SDLDeleteInteractionChoiceSetResponse.h"
#import "RPC/SDLDeleteSubMenuResponse.h"
#import "RPC/SDLOnHMIStatus.h"
#import "RPC/SDLOnButtonEvent.h"
#import "RPC/SDLOnButtonPress.h"
#import "RPC/SDLOnCommand.h"
#import "RPC/SDLOnEncodedSyncPData.h"
#import "RPC/SDLOnTBTClientState.h"
#import "RPC/SDLOnDriverDistraction.h"
#import "RPC/SDLOnAppInterfaceUnregistered.h"
#import "RPC/SDLPerformInteractionResponse.h"
#import "RPC/SDLRegisterAppInterfaceResponse.h"
#import "RPC/SDLSetGlobalPropertiesResponse.h"
#import "RPC/SDLResetGlobalPropertiesResponse.h"
#import "RPC/SDLSetMediaClockTimerResponse.h"
#import "RPC/SDLShowResponse.h"
#import "RPC/SDLSpeakResponse.h"
#import "RPC/SDLSubscribeButtonResponse.h"
#import "RPC/SDLUnregisterAppInterfaceResponse.h"
#import "RPC/SDLUnsubscribeButtonResponse.h"
#import "RPC/SDLGenericResponse.h"


// iviLink
#import "IVILinkRPC.h"


@protocol SDLProxyListener 
@optional
-(void) onOnHMIStatus:(SDLOnHMIStatus*) notification;
-(void) onOnEncodedSyncPData:(SDLOnEncodedSyncPData*) notification;
-(void) onOnTBTClientState:(SDLOnTBTClientState*) notification;
-(void) onOnDriverDistraction:(SDLOnDriverDistraction*) notification;
-(void) onOnButtonEvent:(SDLOnButtonEvent*) notification;
-(void) onOnButtonPress:(SDLOnButtonPress*) notification;
-(void) onOnCommand:(SDLOnCommand*) notification;
-(void) onOnAppInterfaceUnregistered:(SDLOnAppInterfaceUnregistered*) notification;

-(void) onAddCommandResponse:(SDLAddCommandResponse*) response;
-(void) onAddSubMenuResponse:(SDLAddSubMenuResponse*) response;
-(void) onAlertResponse:(SDLAlertResponse*) response;
-(void) onCreateInteractionChoiceSetResponse:(SDLCreateInteractionChoiceSetResponse*) response;
-(void) onDeleteCommandResponse:(SDLDeleteCommandResponse*) response;
-(void) onDeleteInteractionChoiceSetResponse:(SDLDeleteInteractionChoiceSetResponse*) response;
-(void) onDeleteSubMenuResponse:(SDLDeleteSubMenuResponse*) response;
-(void) onEncodedSyncPDataResponse:(SDLEncodedSyncPDataResponse*) response;
-(void) onPerformInteractionResponse:(SDLPerformInteractionResponse*) response;
-(void) onRegisterAppInterfaceResponse:(SDLRegisterAppInterfaceResponse*) response;
-(void) onSetGlobalPropertiesResponse:(SDLSetGlobalPropertiesResponse*) response;
-(void) onResetGlobalPropertiesResponse:(SDLResetGlobalPropertiesResponse*) response;
-(void) onSetMediaClockTimerResponse:(SDLSetMediaClockTimerResponse*) response;
-(void) onShowResponse:(SDLShowResponse*) response;
-(void) onSpeakResponse:(SDLSpeakResponse*) response;
-(void) onSubscribeButtonResponse:(SDLSubscribeButtonResponse*) response;
-(void) onUnregisterAppInterfaceResponse:(SDLUnregisterAppInterfaceResponse*) response;
-(void) onUnsubscribeButtonResponse:(SDLUnsubscribeButtonResponse*) response;
-(void) onGenericResponse:(SDLGenericResponse*) response;

-(void) onProxyOpened;
-(void) onProxyClosed;
-(void) onError:(NSException*) e;

// ivilink callbacks
@optional
-(void) onOnProfileToAppMessage: (SDLOnProfileToAppMessage*) notification;
@optional
-(void) onOnProfileUnloaded: (SDLOnProfileUnloaded*)notification;
@optional
-(void) onOnProfileStateChanged:(SDLOnProfileStateChanged*) notification;

@optional
-(void) onAddProfileResponse: (SDLAddProfileResponse*) response;
@optional
-(void) onAppStateChangedResponse: (SDLAppStateChangedResponse*) response;
@optional
-(void) onLoadProfileResponse: (SDLLoadProfileResponse*) response;
@optional
-(void) onRemoveProfileResponse: (SDLLoadProfileResponse*) response;
@optional
-(void) onUnloadProfileResponse: (SDLUnloadProfileResponse*) response;
@optional
-(void) onSendAppToProfileMessageResponse: (SDLSendAppToProfileMessageResponse*) response;

@end
