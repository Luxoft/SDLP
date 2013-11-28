//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLChoice.h"

@interface SDLCreateInteractionChoiceSet : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* interactionChoiceSetID;
@property(assign) NSMutableArray* choiceSet;

@end
