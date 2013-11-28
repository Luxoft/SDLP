//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"

#import "SDLAppInterfaceUnregisteredReason.h"

@interface SDLOnAppInterfaceUnregistered : SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLAppInterfaceUnregisteredReason* reason;

@end
