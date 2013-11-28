//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLRPCRequestFactory.h"
#import "RPC/SDLMenuParams.h"
#import "SDLTTSChunkFactory.h"

#define NGN_MEDIA_SCREEN_APP_NAME_MAX_LENGTH 5

@implementation SDLRPCRequestFactory

+(SDLRegisterAppInterface*) buildRegisterAppInterfaceWithAppName:(NSString*) appName {
	return [SDLRPCRequestFactory buildRegisterAppInterfaceWithAppName:appName isMediaApp:[NSNumber numberWithBool:NO] autoActivateID:@""];
}

+(SDLRegisterAppInterface*) buildRegisterAppInterfaceWithAppName:(NSString*) appName isMediaApp:(NSNumber*) isMediaApp autoActivateID:(NSString*) autoActivateID  {
		
	SDLRegisterAppInterface* msg = [[[SDLRegisterAppInterface alloc] init] autorelease];
	msg.correlationID = [NSNumber numberWithInt:1];
	msg.appName = appName;
	SDLMsgVersion* version = [[[SDLMsgVersion alloc] init] autorelease];
	version.majorVersion = [NSNumber numberWithInt:1];
	version.minorVersion = [NSNumber numberWithInt:1];
	msg.syncMsgVersion = version;
	NSString* ngnMediaAppName = [[appName copy] autorelease];
	if (ngnMediaAppName.length > NGN_MEDIA_SCREEN_APP_NAME_MAX_LENGTH) {
		ngnMediaAppName = [ngnMediaAppName substringToIndex:NGN_MEDIA_SCREEN_APP_NAME_MAX_LENGTH];
	}
	msg.ngnMediaScreenAppName = ngnMediaAppName;
	NSMutableArray* syns = [NSMutableArray arrayWithObject:appName];
	msg.vrSynonyms = syns;
	msg.autoActivateID = autoActivateID;
	msg.isMediaApplication = isMediaApp;
	msg.languageDesired = SDLLanguage.EN_US;
	
	return msg;
	
}

+(SDLUnregisterAppInterface*) buildUnregisterAppInterfaceWithCorrelationID:(NSNumber*) correlationID  {
	SDLUnregisterAppInterface* msg = [[[SDLUnregisterAppInterface alloc] init] autorelease];
	msg.correlationID = correlationID;
	return msg;
}

+(SDLAlert*) buildAlertWithTTS:(NSString*) ttsText alertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 playTone:(NSNumber*) playTone duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID {
	SDLTTSChunk* simpleChunk = [[[SDLTTSChunk alloc] init] autorelease];
	simpleChunk.text = ttsText;
	simpleChunk.type = SDLSpeechCapabilities.TEXT;
	NSArray* ttsChunks = [NSArray arrayWithObject:simpleChunk];
	return [SDLRPCRequestFactory buildAlertWithTTSChunks:ttsChunks alertText1:alertText1 alertText2:alertText2 playTone:playTone duration:duration correlationID:correlationID];
}

+(SDLAlert*) buildAlertWithTTSChunks:(NSArray*) ttsChunks alertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 playTone:(NSNumber*) playTone duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID {
	SDLAlert* msg = [[[SDLAlert alloc] init] autorelease];
	msg.correlationID = correlationID;
	msg.alertText1 = alertText1;
	msg.alertText2 = alertText2;
	msg.ttsChunks = [[ttsChunks mutableCopy] autorelease];
	msg.playTone = playTone;
	msg.duration = duration;
	
	return msg;
}

+(SDLAlert*) buildAlertWithAlertText1:(NSString*) alertText1 alertText2:(NSString*) alertText2 duration:(NSNumber*) duration correlationID:(NSNumber*) correlationID  {
	return [SDLRPCRequestFactory buildAlertWithTTSChunks:nil alertText1: alertText1 alertText2:alertText2 playTone:nil duration:duration correlationID:correlationID];
}
+(SDLAlert*) buildAlertWithTTS:(NSString*) ttsText playTone:(NSNumber*) playTone correlationID:(NSNumber*) 
    correlationID{ 
	return [SDLRPCRequestFactory buildAlertWithTTS:ttsText alertText1:nil alertText2:nil playTone:playTone duration:nil correlationID:correlationID];
}
+(SDLAlert*) buildAlertWithTTSChunks:(NSArray*) ttsChunks playTone:(NSNumber*) playTone correlationID:(NSNumber*) correlationID  {	
	return [SDLRPCRequestFactory buildAlertWithTTSChunks:ttsChunks alertText1:nil alertText2:nil playTone:playTone duration:nil correlationID:correlationID];
}

+(SDLSpeak*) buildSpeakWithTTS:(NSString*) ttsText correlationID:(NSNumber*) correlationID  {
	SDLTTSChunk* simpleChunk = [[[SDLTTSChunk alloc] init] autorelease];
	simpleChunk.text = ttsText;
	simpleChunk.type = SDLSpeechCapabilities.TEXT;
	NSArray* ttsChunks = [NSMutableArray arrayWithObject:simpleChunk];
	return [SDLRPCRequestFactory buildSpeakWithTTSChunks:ttsChunks correlationID:correlationID];
	
}

+(SDLSpeak*) buildSpeakWithTTSChunks:(NSArray*) ttsChunks correlationID:(NSNumber*) correlationID  {
	SDLSpeak* msg = [[[SDLSpeak alloc] init] autorelease];
	msg.correlationID = correlationID;
	msg.ttsChunks = [[ttsChunks mutableCopy] autorelease];
	
	return msg;
}


+(SDLShow*) buildShowWithMainField1:(NSString*) mainField1 mainField2: (NSString*) mainField2 alignment:(SDLTextAlignment*) alignment correlationID:(NSNumber*) correlationID  {
	return [SDLRPCRequestFactory buildShowWithMainField1:mainField1 mainField2:mainField2 statusBar:nil mediaClock:nil mediaTrack:nil alignment:alignment correlationID:correlationID];
}

+(SDLShow*) buildShowWithMainField1:(NSString*) mainField1 mainField2: (NSString*) mainField2 statusBar:(NSString*) statusBar mediaClock:(NSString*) mediaClock mediaTrack:(NSString*) mediaTrack alignment:(SDLTextAlignment*) textAlignment correlationID:(NSNumber*) correlationID  {
	SDLShow* msg = [[[SDLShow alloc] init] autorelease];
	msg.correlationID = correlationID;
	msg.mainField1 = mainField1;
	msg.mainField2 = mainField2;
	msg.statusBar = statusBar;
	msg.mediaClock = mediaClock;
	msg.mediaTrack = mediaTrack;
	msg.alignment = textAlignment;
	
	return msg;
}

+(SDLSetMediaClockTimer*) buildSetMediaClockTimerWithHours:(NSNumber*) hours minutes:(NSNumber*) minutes seconds:(NSNumber*) seconds updateMode:(SDLUpdateMode*) updateMode correlationID:(NSNumber*) correlationID  {
	SDLSetMediaClockTimer* msg = [[[SDLSetMediaClockTimer alloc] init] autorelease];
	SDLStartTime* startTime = [[[SDLStartTime alloc] init] autorelease];
	startTime.hours = hours;
	startTime.minutes = minutes;
	startTime.seconds = seconds;
	msg.startTime = startTime;
	msg.updateMode = updateMode;
	msg.correlationID = correlationID;
	
	return msg;
}
+(SDLSetMediaClockTimer*) buildSetMediaClockTimerWithUpdateMode:(SDLUpdateMode*) updateMode correlationID:(NSNumber*) correlationID  {
	SDLSetMediaClockTimer* msg = [[[SDLSetMediaClockTimer alloc] init] autorelease];
	
	msg.updateMode = updateMode;
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID menuName:(NSString*) menuName parentID:(NSNumber*) parentID position:(NSNumber*) position vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID {
	SDLAddCommand* msg = [[[SDLAddCommand alloc] init] autorelease];
	msg.correlationID = correlationID;

	msg.cmdID = cmdID;

	if (menuName != nil || parentID != nil || position != nil) {
		SDLMenuParams* menuParams = [[[SDLMenuParams alloc] init] autorelease];
		menuParams.menuName = menuName;
		menuParams.parentID = parentID;
		menuParams.position = position;
		msg.menuParams = menuParams;
	}
	msg.vrCommands = [[vrCommands mutableCopy] autorelease];

	return msg;
}

+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID {
	return [SDLRPCRequestFactory buildAddCommandWithID:cmdID menuName:nil vrCommands:vrCommands correlationID:correlationID];
}

+(SDLAddCommand*) buildAddCommandWithID:(NSNumber*) cmdID menuName:(NSString*) menuName vrCommands:(NSArray*) vrCommands correlationID:(NSNumber*) correlationID {
	return [SDLRPCRequestFactory buildAddCommandWithID:cmdID menuName:menuName parentID:nil position:nil vrCommands:vrCommands correlationID:correlationID];
}


+(SDLDeleteCommand*) buildDeleteCommandWithID:(NSNumber*) cmdID correlationID:(NSNumber*) correlationID  {
	SDLDeleteCommand *msg = [[[SDLDeleteCommand alloc] init] autorelease];
	msg.cmdID = cmdID;
	msg.correlationID = correlationID;
	return msg;
}

+(SDLAddSubMenu*) buildAddSubMenuWithID:(NSNumber*) menuID menuName:(NSString*) menuName correlationID:(NSNumber*) correlationID  {
	return [SDLRPCRequestFactory buildAddSubMenuWithID:menuID menuName:menuName position:nil 
                                        correlationID:correlationID];
}

+(SDLAddSubMenu*) buildAddSubMenuWithID:(NSNumber*) menuID menuName:(NSString*) menuName position:(NSNumber*) position correlationID:(NSNumber*) correlationID {
	SDLAddSubMenu* msg = [[[SDLAddSubMenu alloc] init] autorelease];
	msg.correlationID = correlationID;
	msg.menuID = menuID;
	msg.menuName = menuName;
	msg.position = position;
	
	return msg;
}
+(SDLDeleteSubMenu*) buildDeleteSubMenuWithID:(NSNumber*) menuID correlationID:(NSNumber*) correlationID { 
	SDLDeleteSubMenu *msg = [[[SDLDeleteSubMenu alloc] init] autorelease];
	msg.menuID = menuID;
	msg.correlationID = correlationID;

	return msg;
}

+(SDLCreateInteractionChoiceSet*) buildCreateInteractionChoiceSetWithID:(NSNumber*)interactionChoiceSetID choiceSet:(NSArray*) choices correlationID:(NSNumber*) correlationID  {
	SDLCreateInteractionChoiceSet *msg = [[[SDLCreateInteractionChoiceSet alloc] init] autorelease];
	msg.interactionChoiceSetID = interactionChoiceSetID;
	msg.choiceSet = [[choices mutableCopy] autorelease];
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLDeleteInteractionChoiceSet*) buildDeleteInteractionChoiceSetWithID:(NSNumber*)interactionChoiceSetID correlationID:(NSNumber*) correlationID  { 
	SDLDeleteInteractionChoiceSet *msg = [[[SDLDeleteInteractionChoiceSet alloc] init] autorelease];
	msg.interactionChoiceSetID = interactionChoiceSetID;
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSArray*)initialChunks initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpChunks:(NSArray*)helpChunks timeoutChunks:(NSArray*)timeoutChunks interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout correlationID:(NSNumber*) correlationID  {
	SDLPerformInteraction *msg = [[[SDLPerformInteraction alloc] init] autorelease];
	msg.initialPrompt = [[initialChunks mutableCopy] autorelease];
	msg.initialText = initialText;
	msg.interactionChoiceSetIDList = [[interactionChoiceSetIDList mutableCopy] autorelease];
	msg.helpPrompt = [[helpChunks mutableCopy] autorelease];
	msg.timeoutPrompt = [[timeoutChunks mutableCopy] autorelease];
	msg.interactionMode = interactionMode;
	msg.timeout = timeout;
	msg.correlationID = correlationID;
	
	return msg;
}
+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSString*)initialPrompt initialText:(NSString*)initialText interactionChoiceSetIDList:(NSArray*) interactionChoiceSetIDList helpPrompt:(NSString*)helpPrompt timeoutPrompt:(NSString*)timeoutPrompt interactionMode:(SDLInteractionMode*) interactionMode timeout:(NSNumber*)timeout correlationID:(NSNumber*) correlationID  { 
	NSArray* initialChunks = [SDLTTSChunkFactory buildTTSChunksFromSimple:initialPrompt];
	NSArray* helpChunks = [SDLTTSChunkFactory buildTTSChunksFromSimple:helpPrompt];
	NSArray* timeoutChunks = [SDLTTSChunkFactory buildTTSChunksFromSimple:timeoutPrompt];
	
	
	return [SDLRPCRequestFactory buildPerformInteractionWithInitialPrompt:initialChunks initialText:initialText interactionChoiceSetIDList:interactionChoiceSetIDList helpChunks:helpChunks timeoutChunks:timeoutChunks interactionMode:interactionMode timeout:timeout correlationID:correlationID];
}
+(SDLPerformInteraction*) buildPerformInteractionWithInitialPrompt:(NSString*)initialPrompt initialText:(NSString*)initialText interactionChoiceSetID:(NSNumber*) interactionChoiceSetID correlationID:(NSNumber*) correlationID  {
	NSArray *interactionChoiceSetIDList = [NSArray arrayWithObject:interactionChoiceSetID];
	NSArray* initialChunks = [SDLTTSChunkFactory buildTTSChunksFromSimple:initialPrompt];
	
	return [SDLRPCRequestFactory buildPerformInteractionWithInitialPrompt:initialChunks initialText:initialText interactionChoiceSetIDList:interactionChoiceSetIDList helpChunks:nil timeoutChunks:nil interactionMode:SDLInteractionMode.BOTH timeout:nil correlationID:correlationID];
}


+(SDLSubscribeButton*) buildSubscribeButtonWithName:(SDLButtonName*) buttonName correlationID:(NSNumber*) correlationID {
	SDLSubscribeButton* msg = [[[SDLSubscribeButton alloc] init] autorelease];
	msg.correlationID = correlationID;
	msg.buttonName = buttonName;
	
	return msg;
}

+(SDLEncodedSyncPData*) buildEncodedSyncPDataWithData:(NSMutableArray*) data correlationID:(NSNumber*) correlationID {
	SDLEncodedSyncPData *msg = [[[SDLEncodedSyncPData alloc] init] autorelease];
	msg.data = data;
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLUnsubscribeButton*) buildUnsubscribeButtonWithName:(SDLButtonName*) buttonName correlationID:(NSNumber*) correlationID {
	SDLUnsubscribeButton *msg = [[[SDLUnsubscribeButton alloc] init] autorelease];
	msg.buttonName = buttonName;
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLSetGlobalProperties*) buildSetGlobalPropertiesWithHelpText:(NSString*) helpText timeoutText:(NSString*) timeoutText correlationID:(NSNumber*) correlationID {
	SDLSetGlobalProperties* msg = [[[SDLSetGlobalProperties alloc] init] autorelease];
	msg.helpPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:helpText];
	msg.timeoutPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:timeoutText];
	
	msg.correlationID = correlationID;
	
	return msg;
}

+(SDLResetGlobalProperties*) buildResetGlobalPropertiesWithProperties:(NSArray*) properties correlationID:(NSNumber*) correlationID {
	SDLResetGlobalProperties* msg = [[[SDLResetGlobalProperties alloc] init] autorelease];
	msg.properties = [[properties mutableCopy] autorelease];
	
	msg.correlationID = correlationID;
	
	return msg;
}

// iviLink

+(NSArray*) buildAddProfileWithName:(NSString*)name rawData:(NSData*)data correlationID:(NSNumber*) correlationID {
    if (name == nil || data == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    return [ProfileBinaryPacketizer createAddProfileRequestsForData:data forProfile:name withCorrId:[correlationID intValue]];
}

+(NSArray*) buildAddProfileForEmbeddedPath:(NSString*)name profileName: (NSString*)profileName correlationID:(NSNumber*) correlationID {
    if (name == nil || profileName == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    NSString * path = [[NSBundle mainBundle] pathForResource:name ofType:nil];
    NSData * fileData = [NSData dataWithContentsOfFile: path];
    if (fileData == nil) {
        [NSException raise:@"File not found!" format:@"File %@ is not present", name];
    }
    return [SDLRPCRequestFactory buildAddProfileWithName:profileName rawData:fileData correlationID:correlationID];
}

+(SDLRemoveProfile*) buildRemoveProfileWithName:(NSString*)name correlationID:(NSNumber*)correlationID {
    if (name == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    SDLRemoveProfile * msg = [[[SDLRemoveProfile alloc] init] autorelease];
    [msg setProfileName: name];
    [msg setCorrelationID: correlationID];
    return msg;
}

+(SDLLoadProfile*) buildLoadProfileWithName:(NSString*)name correlationID:(NSNumber*)correlationID {
    if (name == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    SDLLoadProfile * msg = [[[SDLLoadProfile alloc] init] autorelease];
    [msg setProfileName: name];
    [msg setCorrelationID: correlationID];
    return msg;
}

+(SDLUnloadProfile*) buildUnloadProfileWithName:(NSString*)name correlationID:(NSNumber*)correlationID {
    if (name == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    SDLUnloadProfile * msg = [[[SDLUnloadProfile alloc] init] autorelease];
    [msg setProfileName: name];
    [msg setCorrelationID: correlationID];
    return msg;
}

+(SDLAppStateChanged*) buildAppStateChangedWithProfileName:(NSString*)name applicationState:(SDLMobileAppState*)state correlationID:(NSNumber*)correlationID {
    if (name == nil || state == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    SDLAppStateChanged * msg = [[[SDLAppStateChanged alloc] init] autorelease];
    [msg setProfileName: name];
    [msg setMobileAppState: state];
    [msg setCorrelationID: correlationID];
    return msg;
}

+(SDLSendAppToProfileMessage*) buildSendAppToProfileMessageWithName: (NSString*)name rawData:(NSData*)data correlationID:(NSNumber*)correlationID {
    if (name == nil || data == nil || correlationID == nil) {
        [NSException raise:@"Invalid params!" format:@"Some of the params are nil!"];
    }
    SDLSendAppToProfileMessage * msg = [[[SDLSendAppToProfileMessage alloc] init] autorelease];
    [msg setProfileName: name];
    [msg setMessageData: data];
    [msg setCorrelationID: correlationID];
    return msg;
}

@end
