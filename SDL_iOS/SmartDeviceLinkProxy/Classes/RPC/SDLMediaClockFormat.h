//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLMediaClockFormat : SDLEnum {}

+(SDLMediaClockFormat*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLMediaClockFormat*) CLOCK1;
+(SDLMediaClockFormat*) CLOCK2;
+(SDLMediaClockFormat*) CLOCKTEXT1;
+(SDLMediaClockFormat*) CLOCKTEXT2;
+(SDLMediaClockFormat*) CLOCKTEXT3;

@end
