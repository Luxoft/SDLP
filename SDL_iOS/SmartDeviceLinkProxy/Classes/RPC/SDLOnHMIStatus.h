//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"

#import "SDLHMILevel.h"
#import "SDLAudioStreamingState.h"
#import "SDLSystemContext.h"

@interface SDLOnHMIStatus : SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) SDLHMILevel* hmiLevel;
@property(assign) SDLAudioStreamingState* audioStreamingState;
@property(assign) SDLSystemContext* systemContext;

@end
