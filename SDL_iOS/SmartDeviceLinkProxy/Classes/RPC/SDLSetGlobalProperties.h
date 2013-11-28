//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLTTSChunk.h"
#import "SDLTTSChunk.h"

@interface SDLSetGlobalProperties : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSMutableArray* helpPrompt;
@property(assign) NSMutableArray* timeoutPrompt;

@end
