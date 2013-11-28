//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"

#import "SDLDisplayType.h"
#import "SDLTextField.h"
#import "SDLMediaClockFormat.h"

@interface SDLDisplayCapabilities : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLDisplayType* displayType;
@property(assign) NSMutableArray* textFields;
@property(assign) NSMutableArray* mediaClockFormats;

@end
