//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLMsgVersion.h"
#import "SDLLanguage.h"

@interface SDLRegisterAppInterface : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLMsgVersion* syncMsgVersion;
@property(assign) NSString* appName;
@property(assign) NSString* ngnMediaScreenAppName;
@property(assign) NSMutableArray* vrSynonyms;
@property(assign) NSNumber* isMediaApplication;
@property(assign) SDLLanguage* languageDesired;
@property(assign) NSString* autoActivateID;

@end
