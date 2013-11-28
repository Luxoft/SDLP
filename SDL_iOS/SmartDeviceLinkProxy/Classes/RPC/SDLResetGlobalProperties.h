//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLGlobalProperty.h"

@interface SDLResetGlobalProperties : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSMutableArray* properties;

@end
