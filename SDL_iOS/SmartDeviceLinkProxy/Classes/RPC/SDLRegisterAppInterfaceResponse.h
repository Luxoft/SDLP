//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCResponse.h"

#import "SDLResult.h"
#import "SDLMsgVersion.h"
#import "SDLLanguage.h"
#import "SDLDisplayCapabilities.h"
#import "SDLButtonCapabilities.h"
#import "SDLHMIZoneCapabilities.h"
#import "SDLSpeechCapabilities.h"
#import "SDLVRCapabilities.h"

@interface SDLRegisterAppInterfaceResponse : SDLRPCResponse {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLMsgVersion* syncMsgVersion;
@property(assign) NSString* autoActivateID;
@property(assign) SDLLanguage* language;
@property(assign) SDLDisplayCapabilities* displayCapabilities;
@property(assign) NSMutableArray* buttonCapabilities;
@property(assign) NSMutableArray* hmiZoneCapabilities;
@property(assign) NSMutableArray* speechCapabilities;
@property(assign) NSMutableArray* vrCapabilities;

@end
