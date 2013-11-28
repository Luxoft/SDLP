//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"

#import "SDLSpeechCapabilities.h"

@interface SDLTTSChunk : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSString* text;
@property(assign) SDLSpeechCapabilities* type;

@end
