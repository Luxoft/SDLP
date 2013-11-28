//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLMenuParams.h"

@interface SDLAddCommand : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* cmdID;
@property(assign) SDLMenuParams* menuParams;
@property(assign) NSMutableArray* vrCommands;

@end
