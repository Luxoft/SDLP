//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"


@interface SDLMsgVersion : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* majorVersion;
@property(assign) NSNumber* minorVersion;

@end
