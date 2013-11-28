//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLTTSChunk.h"
#import "SDLInteractionMode.h"
#import "SDLTTSChunk.h"
#import "SDLTTSChunk.h"

@interface SDLPerformInteraction : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSString* initialText;
@property(assign) NSMutableArray* initialPrompt;
@property(assign) SDLInteractionMode* interactionMode;
@property(assign) NSMutableArray* interactionChoiceSetIDList;
@property(assign) NSMutableArray* helpPrompt;
@property(assign) NSMutableArray* timeoutPrompt;
@property(assign) NSNumber* timeout;

@end
