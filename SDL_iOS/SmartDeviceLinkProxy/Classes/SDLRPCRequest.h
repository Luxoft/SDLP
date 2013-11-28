//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCMessage.h"

@interface SDLRPCRequest : SDLRPCMessage {}

@property(retain) NSNumber* correlationID;

@end
