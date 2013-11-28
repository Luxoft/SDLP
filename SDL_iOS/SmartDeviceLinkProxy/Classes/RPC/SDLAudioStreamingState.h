//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLAudioStreamingState : SDLEnum {}

+(SDLAudioStreamingState*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLAudioStreamingState*) AUDIBLE;
+(SDLAudioStreamingState*) NOT_AUDIBLE;

@end
