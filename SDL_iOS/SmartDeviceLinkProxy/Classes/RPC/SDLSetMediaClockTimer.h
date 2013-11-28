//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLStartTime.h"
#import "SDLUpdateMode.h"

@interface SDLSetMediaClockTimer : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLStartTime* startTime;
@property(assign) SDLUpdateMode* updateMode;

@end
