//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "RPC/SDLRegisterAppInterface.h"
#import "RPC/SDLUnregisterAppInterface.h"
#import "RPC/SDLAlert.h"
#import "RPC/SDLSpeak.h"
#import "RPC/SDLShow.h"
#import "RPC/SDLSetMediaClockTimer.h"
#import "RPC/SDLEncodedSyncPData.h"
#import "RPC/SDLAddCommand.h"
#import "RPC/SDLDeleteCommand.h"
#import "RPC/SDLCreateInteractionChoiceSet.h"
#import "RPC/SDLDeleteInteractionChoiceSet.h"
#import "RPC/SDLPerformInteraction.h"
#import "RPC/SDLAddSubMenu.h"
#import "RPC/SDLDeleteSubMenu.h"
#import "RPC/SDLSubscribeButton.h"
#import "RPC/SDLUnsubscribeButton.h"
#import "RPC/SDLResetGlobalProperties.h"
#import "RPC/SDLSetGlobalProperties.h"

#import "IVILinkRPC.h"

@interface SDLRPCRequestFactory : NSObject {}

+(SDLRegisterAppInterface*) buildRegisterAppInterfaceWithAppName:(NSString*) appName;
+(SDLRegisterAppInterface*) buildRegisterAppInterfaceWithAppName:(NSString*) appName isMediaApp:(NSNumber*) isMediaApp autoActivateID:(NSString*) autoActivateID;

+(SDLUnregisterAppInterface*) buildUnregisterAppInterfaceWithCorrelationID:(NSNumber*) correlationID;

+(SDLAlert*) buildAlertWithTTS:(NSString*) ttsText alertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 playTone:(NSNumber*) playTone duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID;
+(SDLAlert*) buildAlertWithTTSChunks:(NSArray*) ttsChunks alertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 playTone:(NSNumber*) playTone duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID;
+(SDLAlert*) buildAlertWithAlertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID;
+(SDLAlert*) buildAlertWithTTS:(NSString*) ttsText playTone:(NSNumber*) playTone correlationID:(NSNumber*) correlationID;
+(SDLAlert*) buildAlertWithTTSChunks:(NSArray*) ttsChunks playTone:(NSNumber*) playTone correlationID:(NSNumber*) correlationID;

+(SDLSpeak*) buildSpeakWithTTS:(NSString*) ttsText correlationID:(NSNumber*) correlationID;
+(SDLSpeak*) buildSpeakWithTTSChunks:(NSArray*) ttsChunks correlationID:(NSNumber*) correlationID;

+(SDLShow*) buildShowWithMainField1:(NSString*) mainField1 mainField2: (NSString*) mainField2 alignment:(SDLTextAlignment*) textAlignment correlationID:(NSNumber*) correlationID;
+(SDLShow*) buildShowWithMainField1:(NSString*) mainField1 mainField2: (NSString*) mainField2 statusBar:(NSString*) statusBar mediaClock:(NSString*) mediaClock mediaTrack:(NSString*) mediaTrack alignment:(SDLTextAlignment*) textAlignment correlationID:(NSNumber*) correlationID;

+(SDLSetMediaClockTimer*) buildSetMediaClockTimerWithHours:(NSNumber*) hours minutes:(NSNumber*) minutes seconds:(NSNumber*) seconds updateMode:(SDLUpdateMode*) updateMode correlationID:(NSNumber*) correlationID;
+(SDLSetMediaClockTimer*) buildSetMediaClockTimerWithUpdateMode:(SDLUpdateMode*) updateMode correlationID:(NSNumber*) correlationID;

+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID menuName:(NSString*) menuName parentID:(NSNumber*) parentID position:(NSNumber*) position vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID;
+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID;
+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID menuName:(NSString*) menuName vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID;

+(SDLDeleteCommand*) buildDeleteCommandWithID:(NSNumber*) cmdID correlationID:(NSNumber*) correlationID;

+(SDLAddSubMenu*) buildAddSubMenuWithID:(NSNumber*) menuID menuName:(NSString*) menuName position:(NSNumber*) position correlationID:(NSNumber*) correlationID;
+(SDLAddSubMenu*) buildAddSubMenuWithID:(NSNumber*) menuID menuName:(NSString*) menuName correlationID:(NSNumber*) correlationID;

+(SDLDeleteSubMenu*) buildDeleteSubMenuWithID:(NSNumber*) menuID correlationID:(NSNumber*) correlationID;

+(SDLCreateInteractionChoiceSet*) buildCreateInteractionChoiceSetWithID:(NSNumber*)interactionChoiceSetID choiceSet:(NSArray*) choices correlationID:(NSNumber*) correlationID;

+(SDLDeleteInteractionChoiceSet*) buildDeleteInteractionChoiceSetWithID:(NSNumber*)interactionChoiceSetID correlationID:(NSNumber*) correlationID;

+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSArray*)initialChunks initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpChunks:(NSArray*)helpChunks timeoutChunks:(NSArray*)timeoutChunks interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout correlationID:(NSNumber*) correlationID;
+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSString*)initialPrompt initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpPrompt:(NSString*)helpPrompt timeoutPrompt:(NSString*)timeoutPrompt interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout correlationID:(NSNumber*) correlationID;
+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSString*)initialPrompt initialText:(NSString*)initialText interactionChoiceSetID:(NSNumber*) interactionChoiceSetID correlationID:(NSNumber*) correlationID;
	
+(SDLSubscribeButton*) buildSubscribeButtonWithName:(SDLButtonName*) buttonName correlationID:(NSNumber*) correlationID;

+(SDLUnsubscribeButton*) buildUnsubscribeButtonWithName:(SDLButtonName*) buttonName correlationID:(NSNumber*) correlationID;

+(SDLEncodedSyncPData*) buildEncodedSyncPDataWithData:(NSMutableArray*) data correlationID:(NSNumber*) correlationID;

+(SDLSetGlobalProperties*) buildSetGlobalPropertiesWithHelpText:(NSString*) helpText timeoutText:(NSString*) timeoutText correlationID:(NSNumber*) correlationID;

+(SDLResetGlobalProperties*) buildResetGlobalPropertiesWithProperties:(NSArray*) properties correlationID:(NSNumber*) correlationID;

// iviLink PM Support
+(NSArray*) buildAddProfileWithName:(NSString*)name rawData:(NSData*)data correlationID:(NSNumber*)correlationID;
+(NSArray*) buildAddProfileForEmbeddedPath:(NSString*)name profileName: (NSString*)profileName correlationID:(NSNumber*)correlationID;
+(SDLRemoveProfile*) buildRemoveProfileWithName:(NSString*)name correlationID:(NSNumber*)correlationID;
+(SDLLoadProfile*) buildLoadProfileWithName:(NSString*)name correlationID:(NSNumber*)correlationID;
+(SDLUnloadProfile*) buildUnloadProfileWithName:(NSString*)name  correlationID:(NSNumber*)correlationID;
+(SDLAppStateChanged*) buildAppStateChangedWithProfileName:(NSString*)name applicationState:(SDLMobileAppState*)state correlationID:(NSNumber*)correlationID;
+(SDLSendAppToProfileMessage*) buildSendAppToProfileMessageWithName: (NSString*)name rawData:(NSData*)data correlationID:(NSNumber*)correlationID;
@end
