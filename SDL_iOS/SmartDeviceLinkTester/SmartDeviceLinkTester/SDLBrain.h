//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SDLProxyFactory.h"
#import "SDLProxy.h" 
#import "SDLIAPTransport.h"
#import "SDLProtocol.h"
#import "SDLDebugTool.h"
#import "SDLConsoleController.h"
#import "SDLRPCRequest.h"
#import <AVFoundation/AVFoundation.h>

#import "SDLTcpDiscovererDefaultListenerDelegate.h"

@interface SDLBrain : NSObject   <SDLProxyListener, SDLTcpDiscovererDefaultListenerDelegate> {
    SDLProxy* proxy;
    int autoIncCorrID;

    int cmdID;
    BOOL firstTimeStartUp;
}

+(SDLBrain *)getInstance;

-(int)getCMDID;

-(void) setupProxy;
-(void) setup;
-(void) sendRPCMessage:(SDLRPCRequest *)rpcMsg;

-(void) showPressed:(NSString *)message;
-(void) showAdvancedPressedWithLine1Text:(NSString *)line1Text line2:(NSString *)line2Text statusBar:(NSString *)statusBar mediaClock:(NSString *)mediaClock mediaTrack:(NSString *)mediaTrack alignment:(SDLTextAlignment *)textAlignment;
-(void) speakPressed:(NSString *)message;
-(void) speakTTSChunksPressed;
-(void) unregisterAppInterfacePressed;
-(void) setMediaClockTimerPressedwithHours:(NSNumber *)hours minutes:(NSNumber *)minutes seconds:(NSNumber *)seconds updateMode:(SDLUpdateMode *)updateMode;
-(void) alertPressed:(NSString *)message;
-(void) alertAdvancedPressedwithTTSChunks:(NSArray *)ttsChucks alertText1:(NSString *)alertText1 alertText2:(NSString *)alertText2 playTone:(NSNumber *)playTone duration:(NSNumber *)duration;
-(void) addCommand:(NSString *)message;
-(void) addAdvancedCommandPressedwithMenuName:(NSString *)menuName position:(NSNumber *)position parentID:(NSNumber *)parentID vrCommands:(NSArray *) vrCommands;
-(void) deleteCommandPressed:(NSNumber *)cmdID;
-(void) addSubMenuPressedwithID:(NSNumber *)menuID menuName:(NSString *)menuName position:(NSNumber *)position; 
-(void) deleteSubMenuPressedwithID:(NSNumber *)menuID;
-(void) createInteractionChoiceSetPressedWithID:(NSNumber *)interactionChoiceSetID choiceSet:(NSArray *)choices;
-(void) deleteInteractionChoiceSetPressedWithID:(NSNumber *)interactionChoiceSetID;
-(void) performInteractionPressedwithInitialPrompt:(NSArray*)initialChunks initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpChunks:(NSArray*)helpChunks timeoutChunks:(NSArray*)timeoutChunks interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout;
-(void) subscribeButtonPressed:(SDLButtonName *)buttonName;
-(void) unsubscribeButtonPressed:(SDLButtonName *)buttonName;
-(void) sendEncodedSyncPData:(NSMutableArray *)data;
-(void) setGlobalPropertiesPressedWithHelpText:(NSString *)helpText timeoutText:(NSString *)timeoutText;
-(void) resetGlobalPropertiesPressedwithProperties:(NSArray *)properties;

// iviLink
-(void) loadProfile:(NSString*)profileName;
-(void) unloadProfile:(NSString*)profileName;
-(void) sendMessageToProfile:(NSString*)profileName rawData:(NSData*)data;
-(void) applicationStateChanged:(NSString*)profileName mobileAppState:(SDLMobileAppState*)state; // TODO enum
-(void) addProfile:(NSString*)profileName;
-(void) removeProfile:(NSString*)profileName;

@end


