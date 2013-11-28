//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"
#import "SDLDriverDistractionState.h"

@interface SDLOnDriverDistraction: SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLDriverDistractionState* state;

@end

