//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"
#import "RPC/SDLResult.h"

@interface SDLRPCResponse : SDLRPCMessage {}

@property(retain) NSNumber* correlationID;

@property(retain) NSNumber* success;
@property(assign) SDLResult* resultCode;
@property(retain) NSString* info;

-(bool) isSuccess;

@end
