//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"

@interface SDLStartTime : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* hours;
@property(assign) NSNumber* minutes;
@property(assign) NSNumber* seconds;

@end
