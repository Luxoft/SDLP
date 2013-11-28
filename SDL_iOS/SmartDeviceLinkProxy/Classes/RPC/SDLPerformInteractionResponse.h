//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCResponse.h"

#import "SDLResult.h"
#import "SDLTriggerSource.h"

@interface SDLPerformInteractionResponse : SDLRPCResponse {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSNumber* choiceID;
@property(assign) SDLTriggerSource* triggerSource;

@end
