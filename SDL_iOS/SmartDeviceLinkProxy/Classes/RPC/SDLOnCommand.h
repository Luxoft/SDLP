//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"

#import "SDLTriggerSource.h"

@interface SDLOnCommand : SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* cmdID;
@property(assign) SDLTriggerSource* triggerSource;

@end
