//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLButtonName.h"

@interface SDLSubscribeButton : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLButtonName* buttonName;

@end
