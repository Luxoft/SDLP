//
// Copyright (c) 2013 Ford Motor Company
//


#import "SDLTcpDiscoverer.h"

#import "SDLBrain.h"
#import "SDLNames.h"
#import "SDLTTSChunkFactory.h"
#import "SDLGenericResponse.h"
#import "SDLProxyFactory.h"
#import "SDLIAPTransport.h"
#import "SDLProtocol.h"
#import "SDLDebugTool.h"
#import "SDLConsoleController.h"
#import "SDLVersion.h"
#import "SDLLoadProfile.h"
#import <MediaPlayer/MediaPlayer.h>


#define PREFS_MTU_SIZE @"mtuSize"
#define PREFS_SEND_DELAY @"sendDelay"  

#define PREFS_FIRST_RUN @"firstRun"

#define PREFS_PROTOCOL @"protocol"
#define PREFS_IPADDRESS @"ipaddress"
#define PREFS_PORT @"port"

#define PREFS_TYPE @"type"

@interface SDLBrain()
{
    SDLTcpDiscoverer * mDiscoverer;
}
@end

@implementation SDLBrain  

static SDLBrain *gInstance = NULL; 

+ (SDLBrain *)getInstance
{
	@synchronized(self)
	{
		if (gInstance == NULL)
			gInstance = [[self alloc] init];
	}
	return gInstance;
}

//Populating Sync Display Screen with relevant information upon creation
-(void) setup {
    SDLShow* msg = [SDLRPCRequestFactory buildShowWithMainField1:@"Smart Device" mainField2:@"Link Tester" alignment:[SDLTextAlignment CENTERED] correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
	msg.mediaTrack = @"SDL";
    [proxy sendRPCRequest:msg];
    
    [SDLDebugTool logInfo:@"SDLProxy Version: %@: ", VERSION_STRING];
}

-(void) sendRPCMessage:(SDLRPCRequest *)rpcMsg {
    [proxy sendRPCRequest:rpcMsg];
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:rpcMsg]];

}


// =====================================
// RPC Function Calls
// =====================================

- (void) showPressed:(NSString *)message {    
    SDLShow* msg = [SDLRPCRequestFactory buildShowWithMainField1:message mainField2:@"SDL Tester" alignment:[SDLTextAlignment CENTERED] correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
	msg.mediaTrack = @"SDL";
    [proxy sendRPCRequest:msg];
    
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:msg]];
    
}



-(void) showAdvancedPressedWithLine1Text:(NSString *)line1Text line2:(NSString *)line2Text statusBar:(NSString *)statusBar mediaClock:(NSString *)mediaClock mediaTrack:(NSString *)mediaTrack alignment:(SDLTextAlignment *)textAlignment {
    
    SDLShow *msg = [SDLRPCRequestFactory buildShowWithMainField1:line1Text mainField2:line2Text statusBar:statusBar mediaClock:mediaClock mediaTrack:mediaTrack alignment:textAlignment correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:msg];
    
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:msg]];
}

-(void) unregisterAppInterfacePressed {
	SDLUnregisterAppInterface* req = [SDLRPCRequestFactory buildUnregisterAppInterfaceWithCorrelationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) setMediaClockTimerPressedwithHours:(NSNumber *)hours minutes:(NSNumber *)minutes seconds:(NSNumber *)seconds updateMode:(SDLUpdateMode *)updateMode {
    SDLSetMediaClockTimer *req = [SDLRPCRequestFactory buildSetMediaClockTimerWithHours:hours minutes:minutes seconds:seconds updateMode:updateMode correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

- (void) speakPressed:(NSString *)message {
    SDLSpeak* req = [SDLRPCRequestFactory buildSpeakWithTTS:message correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

- (void) alertPressed:(NSString *)message {
    SDLAlert* req = [SDLRPCRequestFactory buildAlertWithTTS:message alertText1:message alertText2:@"" playTone:[NSNumber numberWithBool:YES] duration:[NSNumber numberWithInt:5000] correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) alertAdvancedPressedwithTTSChunks:(NSArray *)ttsChucks alertText1:(NSString *)alertText1 alertText2:(NSString *)alertText2 playTone:(NSNumber *)playTone duration:(NSNumber *)duration {
    
    SDLAlert *req = [SDLRPCRequestFactory buildAlertWithTTSChunks:ttsChucks alertText1:alertText1 alertText2:alertText2 playTone:playTone duration:duration correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) addCommand:(NSString *)message {
    
    NSArray *vrc = [NSArray arrayWithObjects:message, nil];
    SDLAddCommand *command = [SDLRPCRequestFactory buildAddCommandWithID:[NSNumber numberWithInt:cmdID] menuName:message vrCommands:vrc correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:command];
    cmdID++;
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:command]];
    

	
}

-(void) addAdvancedCommandPressedwithMenuName:(NSString *)menuName position:(NSNumber *)position parentID:(NSNumber *)parentID vrCommands:(NSArray *) vrCommands {
    
    [SDLDebugTool logInfo:@"Added addCommand with cmdID = %d and correlationID = %d", cmdID, autoIncCorrID];
    
    SDLAddCommand *command = [SDLRPCRequestFactory buildAddCommandWithID:[NSNumber numberWithInt:cmdID] menuName:menuName parentID:parentID position:position vrCommands:vrCommands correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:command];
    cmdID++;

    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:command]];
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"AddCommandRequest" object:command]];
                                                                                                                                                                
}

- (void) speakTTSChunksPressed {
    SDLSpeak* req = [SDLRPCRequestFactory buildSpeakWithTTS:@"Speak, here comes a jingle" correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [(NSMutableArray*)req.ttsChunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:SDLJingle.INITIAL_JINGLE type:SDLSpeechCapabilities.PRE_RECORDED]];
	[(NSMutableArray*)req.ttsChunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:@", ah, that's nice. Now example of SAPI Phonemes. Live." type:SDLSpeechCapabilities.TEXT]];
    [(NSMutableArray*)req.ttsChunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:@"_ l ay v ." type:SDLSpeechCapabilities.SAPI_PHONEMES]];
    [(NSMutableArray*)req.ttsChunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:@", Read." type:SDLSpeechCapabilities.TEXT]];
    [(NSMutableArray*)req.ttsChunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:@"_ R eh d ." type:SDLSpeechCapabilities.SAPI_PHONEMES]];
    [proxy sendRPCRequest:req];
    
     [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) deleteCommandPressed:(NSNumber *)commandID {
    SDLDeleteCommand *req = [SDLRPCRequestFactory buildDeleteCommandWithID:commandID correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) addSubMenuPressedwithID:(NSNumber *)menuID menuName:(NSString *)menuName position:(NSNumber *)position {
    SDLAddSubMenu *req = [SDLRPCRequestFactory buildAddSubMenuWithID:menuID menuName:menuName position:position correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
    
     [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"AddSubMenuRequest" object:req]];
}

-(void) deleteSubMenuPressedwithID:(NSNumber *)menuID {
    SDLDeleteSubMenu *req = [SDLRPCRequestFactory buildDeleteSubMenuWithID:menuID correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) createInteractionChoiceSetPressedWithID:(NSNumber *)interactionChoiceSetID choiceSet:(NSArray *)choices {
    SDLCreateInteractionChoiceSet *req = [SDLRPCRequestFactory buildCreateInteractionChoiceSetWithID:interactionChoiceSetID choiceSet:choices correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) deleteInteractionChoiceSetPressedWithID:(NSNumber *)interactionChoiceSetID {
    SDLDeleteInteractionChoiceSet *req = [SDLRPCRequestFactory buildDeleteInteractionChoiceSetWithID:interactionChoiceSetID correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) performInteractionPressedwithInitialPrompt:(NSArray*)initialChunks initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpChunks:(NSArray*)helpChunks timeoutChunks:(NSArray*)timeoutChunks interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout {
    
    SDLPerformInteraction *req = [SDLRPCRequestFactory buildPerformInteractionWithInitialPrompt:initialChunks initialText:initialText interactionChoiceSetIDList:interactionChoiceSetIDList helpChunks:helpChunks timeoutChunks:timeoutChunks interactionMode:interactionMode timeout:timeout correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) subscribeButtonPressed:(SDLButtonName *)buttonName {
    SDLSubscribeButton *req = [SDLRPCRequestFactory buildSubscribeButtonWithName:buttonName correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"SubscribeButtonRequest" object:req]];
    
}

-(void) unsubscribeButtonPressed:(SDLButtonName *)buttonName {
    SDLUnsubscribeButton *req = [SDLRPCRequestFactory buildUnsubscribeButtonWithName:buttonName correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) sendEncodedSyncPData:(NSMutableArray *)data {
    SDLEncodedSyncPData* req = [SDLRPCRequestFactory buildEncodedSyncPDataWithData:data correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) setGlobalPropertiesPressedWithHelpText:(NSString *)helpText timeoutText:(NSString *)timeoutText {
    SDLSetGlobalProperties *req = [SDLRPCRequestFactory buildSetGlobalPropertiesWithHelpText:helpText timeoutText:timeoutText correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) resetGlobalPropertiesPressedwithProperties:(NSArray *)properties {
    SDLResetGlobalProperties *req = [SDLRPCRequestFactory buildResetGlobalPropertiesWithProperties:properties correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}


-(int)getCMDID {
    return cmdID;
}

// =====================================
// Proxy Life Management Functions
// =====================================

-(void) savePreferences {
	
	int mtuSize = 1000, delayAfterSend = 0;
	
	NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    
	[prefs setObject:[NSString stringWithFormat:@"%i", mtuSize] forKey:PREFS_MTU_SIZE];
	[prefs setObject:[NSString stringWithFormat:@"%i", delayAfterSend] forKey:PREFS_SEND_DELAY];
    
    //Set to match settings.bundle defaults
    if (![[prefs objectForKey:PREFS_FIRST_RUN] isEqualToString:@"False"]) {
        [prefs setObject:@"False" forKey:PREFS_FIRST_RUN];
        [prefs setObject:@"tcpauto" forKey:PREFS_PROTOCOL];
        [prefs setObject:@"192.168.0.1" forKey:PREFS_IPADDRESS];
        [prefs setObject:@"50007" forKey:PREFS_PORT];
        [prefs setObject:@"media" forKey:PREFS_TYPE];
    }

	[prefs synchronize];
}


-(void)  setupProxy{
    [self savePreferences];
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    if ([[prefs objectForKey:PREFS_PROTOCOL] isEqualToString:@"tcpl"]) {
        proxy = [[SDLProxyFactory buildProxyWithListener: self
                                                   tcpIPAddress: nil
                                                        tcpPort: [prefs objectForKey:PREFS_PORT]] retain];
    } else if ([[prefs objectForKey:PREFS_PROTOCOL] isEqualToString:@"tcps"]) {
        proxy = [[SDLProxyFactory buildProxyWithListener: self
                                                   tcpIPAddress: [prefs objectForKey:PREFS_IPADDRESS]
                                                        tcpPort: [prefs objectForKey:PREFS_PORT]] retain];
    } else if([[prefs objectForKey:PREFS_PROTOCOL] isEqualToString:@"tcpauto"]) {
        mDiscoverer = [[SDLTcpDiscoverer alloc] initWithDefaultListener:self];
        [mDiscoverer performSearch];
    } else
        proxy = [[SDLProxyFactory buildProxyWithListener: self] retain];
     
    
    autoIncCorrID = 101;
    cmdID = 1;
}

-(void) tearDownProxy {
	
	[proxy dispose];
	[SDLDebugTool logInfo:@"Proxy retain count = %i", proxy.retainCount];
	[SDLDebugTool logInfo:@"releasing proxy"];
	[proxy release];
	proxy = nil;
}


// =====================================
// Implementation of ProxyListener
// =====================================

-(void) onOnHMIStatus:(SDLOnHMIStatus*) notification {
    if (notification.hmiLevel == SDLHMILevel.HMI_FULL) {
        if (firstTimeStartUp == YES) {
            [self setup];
            firstTimeStartUp = NO;
        }
    }

    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}   


-(void) onOnButtonEvent:(SDLOnButtonEvent*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}
-(void) onOnButtonPress:(SDLOnButtonPress*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}
-(void) onOnCommand:(SDLOnCommand*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}
-(void) onOnAppInterfaceUnregistered:(SDLOnAppInterfaceUnregistered*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}

-(void) onAddCommandResponse:(SDLAddCommandResponse*) response {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onAddSubMenuResponse:(SDLAddSubMenuResponse*) response {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onCreateInteractionChoiceSetResponse:(SDLCreateInteractionChoiceSetResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onDeleteCommandResponse:(SDLDeleteCommandResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onDeleteInteractionChoiceSetResponse:(SDLDeleteInteractionChoiceSetResponse*) response {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];}
-(void) onDeleteSubMenuResponse:(SDLDeleteSubMenuResponse*) response {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];}
-(void) onPerformInteractionResponse:(SDLPerformInteractionResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onRegisterAppInterfaceResponse:(SDLRegisterAppInterfaceResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onSetGlobalPropertiesResponse:(SDLSetGlobalPropertiesResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onResetGlobalPropertiesResponse:(SDLResetGlobalPropertiesResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onSetMediaClockTimerResponse:(SDLSetMediaClockTimerResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}

-(void) onShowResponse:(SDLShowResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}

-(void) onSpeakResponse:(SDLSpeakResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onAlertResponse:(SDLAlertResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onSubscribeButtonResponse:(SDLSubscribeButtonResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onUnregisterAppInterfaceResponse:(SDLUnregisterAppInterfaceResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onUnsubscribeButtonResponse:(SDLUnsubscribeButtonResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}
-(void) onGenericResponse:(SDLGenericResponse*) response
{
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:response]];
}


-(void) onEncodedSyncPDataResponse:(SDLEncodedSyncPDataResponse*) response {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"onRPCResponse" object:response]];
}

-(void) onOnDriverDistraction:(SDLOnDriverDistraction*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}
-(void) onOnTBTClientState:(SDLOnTBTClientState*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}
-(void) onOnEncodedSyncPData:(SDLOnEncodedSyncPData*) notification {
	[[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:notification]];
}

-(void) onProxyOpened {
    firstTimeStartUp = YES;
    
    SDLRegisterAppInterface* regRequest = [SDLRPCRequestFactory buildRegisterAppInterfaceWithAppName:@"SDLTester"];
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    if ([[prefs objectForKey:PREFS_TYPE] isEqualToString:@"nonmedia"]) {
        regRequest.isMediaApplication = [NSNumber numberWithBool:NO];
    } else {
        regRequest.isMediaApplication = [NSNumber numberWithBool:YES];
    }
    
    regRequest.ngnMediaScreenAppName = nil;
	regRequest.vrSynonyms = nil;
    [proxy sendRPCRequest:regRequest];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:regRequest]];
}

-(void) onError:(NSException*) e {
	[SDLDebugTool logInfo:@"proxy error occurred: %@", e];
}

-(void) onProxyClosed {
    [SDLDebugTool logInfo:@"onProxyClosed"];
    
	[self tearDownProxy];
	
	[[self init] setupProxy];
}

// Profile Manager callbacks

-(void) onOnProfileToAppMessage: (SDLOnProfileToAppMessage*) notification {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:notification]];
    NSString * messageString = [notification messageDataToString];
    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:[notification profileName] message:messageString delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [alert show];
    [alert release];
}


-(void) onOnProfileStateChanged:(SDLOnProfileStateChanged*) notification {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:notification]];
    NSString * messageString = [[notification profileState] value];
    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:[notification profileName] message:messageString delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

-(void) onOnProfileUnloaded:(SDLOnProfileUnloaded *)notification {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:notification]];
    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"Profile Unloaded!" message:[notification profileName] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [alert show];
    [alert release];
    [self setup];
}

-(void) onAddProfileResponse: (SDLAddProfileResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}

-(void) onAppStateChangedResponse: (SDLAppStateChangedResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}
-(void) onLoadProfileResponse: (SDLLoadProfileResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}
-(void) onRemoveProfileResponse: (SDLLoadProfileResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}

-(void) onUnloadProfileResponse: (SDLUnloadProfileResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}
-(void) onSendAppToProfileMessageResponse: (SDLSendAppToProfileMessageResponse*) response{
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject"
                                                                                         object:response]];
}

// TCP device discovery listener
-(void)onFoundNothing {
    NSLog(@"perform search");
    [mDiscoverer performSearch];
}

-(void)onUserCanceledAlert {
    NSLog(@"on user cancel");
    [mDiscoverer performSearch];
}

-(void)onUserSelectedDeviceWithIP:(NSString *)ipaddress tcpPort:(NSString *)port {
    NSLog(@"onUserSelectedDeviceWithIP: %@, %@", ipaddress, port);
    proxy = [[SDLProxyFactory buildProxyWithListener: self
                                        tcpIPAddress: ipaddress
                                             tcpPort: port] retain];
}

-(NSString*) dismissButtonTitle {
    return @"Continue searching";
}


-(void) loadProfile:(NSString*)profileName {
    SDLLoadProfile *req = [SDLRPCRequestFactory buildLoadProfileWithName:profileName
                                                           correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) unloadProfile:(NSString*)profileName {
    SDLUnloadProfile *req = [SDLRPCRequestFactory buildUnloadProfileWithName:profileName
                                                               correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) sendMessageToProfile:(NSString*)profileName rawData:(NSData*)data {
    SDLSendAppToProfileMessage *req = [SDLRPCRequestFactory buildSendAppToProfileMessageWithName:profileName
                                                                                         rawData:data
                                                                                   correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) applicationStateChanged:(NSString*)profileName mobileAppState:(SDLMobileAppState*)state {
    SDLAppStateChanged *req = [SDLRPCRequestFactory buildAppStateChangedWithProfileName:profileName
                                                                       applicationState:state
                                                                          correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}

-(void) addProfile:(NSString*)profileName{
    NSArray * req = [SDLRPCRequestFactory buildAddProfileForEmbeddedPath: @"libSampleProfile.so" profileName:profileName correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    for (id request in req)
    {
        [proxy sendRPCRequest:request];
        [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:request]];
    }
}

-(void) removeProfile:(NSString*)profileName {
    SDLRemoveProfile *req = [SDLRPCRequestFactory buildRemoveProfileWithName:profileName correlationID:[NSNumber numberWithInt:autoIncCorrID++]];
    [proxy sendRPCRequest:req];
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"NewConsoleControllerObject" object:req]];
}


@end
