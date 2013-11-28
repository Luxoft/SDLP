//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"

#import "SDLButtonName.h"
#import "SDLButtonEventMode.h"

@interface SDLOnButtonEvent : SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLButtonName* buttonName;
@property(assign) SDLButtonEventMode* buttonEventMode;

@end
