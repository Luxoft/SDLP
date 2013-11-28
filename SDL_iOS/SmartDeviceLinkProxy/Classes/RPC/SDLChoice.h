//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"


@interface SDLChoice : SDLRPCStruct {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* choiceID;
@property(assign) NSString* menuName;
@property(assign) NSMutableArray* vrCommands;

@end
