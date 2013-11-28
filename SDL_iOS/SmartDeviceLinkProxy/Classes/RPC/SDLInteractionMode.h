//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLInteractionMode : SDLEnum {}

+(SDLInteractionMode*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLInteractionMode*) MANUAL_ONLY;
+(SDLInteractionMode*) VR_ONLY;
+(SDLInteractionMode*) BOTH;

@end
