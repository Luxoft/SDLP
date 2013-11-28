//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLMediaClockFormat.h"

SDLMediaClockFormat* SDLMediaClockFormat_CLOCK1 = nil;
SDLMediaClockFormat* SDLMediaClockFormat_CLOCK2 = nil;
SDLMediaClockFormat* SDLMediaClockFormat_CLOCKTEXT1 = nil;
SDLMediaClockFormat* SDLMediaClockFormat_CLOCKTEXT2 = nil;
SDLMediaClockFormat* SDLMediaClockFormat_CLOCKTEXT3 = nil;

NSMutableArray* SDLMediaClockFormat_values = nil;
@implementation SDLMediaClockFormat

+(SDLMediaClockFormat*) valueOf:(NSString*) value {
    for (SDLMediaClockFormat* item in SDLMediaClockFormat.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLMediaClockFormat_values == nil) {
        SDLMediaClockFormat_values = [[NSMutableArray alloc] initWithObjects:
                SDLMediaClockFormat.CLOCK1,
                SDLMediaClockFormat.CLOCK2,
                SDLMediaClockFormat.CLOCKTEXT1,
                SDLMediaClockFormat.CLOCKTEXT2,
                SDLMediaClockFormat.CLOCKTEXT3,
                nil];
    }
    return SDLMediaClockFormat_values;
}

+(SDLMediaClockFormat*) CLOCK1 {
    	if (SDLMediaClockFormat_CLOCK1 == nil) {
        		SDLMediaClockFormat_CLOCK1 = [[SDLMediaClockFormat alloc] initWithValue:@"CLOCK1"];
    	}
    	return SDLMediaClockFormat_CLOCK1;
}

+(SDLMediaClockFormat*) CLOCK2 {
    	if (SDLMediaClockFormat_CLOCK2 == nil) {
        		SDLMediaClockFormat_CLOCK2 = [[SDLMediaClockFormat alloc] initWithValue:@"CLOCK2"];
    	}
    	return SDLMediaClockFormat_CLOCK2;
}

+(SDLMediaClockFormat*) CLOCKTEXT1 {
    	if (SDLMediaClockFormat_CLOCKTEXT1 == nil) {
        		SDLMediaClockFormat_CLOCKTEXT1 = [[SDLMediaClockFormat alloc] initWithValue:@"CLOCKTEXT1"];
    	}
    	return SDLMediaClockFormat_CLOCKTEXT1;
}

+(SDLMediaClockFormat*) CLOCKTEXT2 {
    	if (SDLMediaClockFormat_CLOCKTEXT2 == nil) {
        		SDLMediaClockFormat_CLOCKTEXT2 = [[SDLMediaClockFormat alloc] initWithValue:@"CLOCKTEXT2"];
    	}
    	return SDLMediaClockFormat_CLOCKTEXT2;
}

+(SDLMediaClockFormat*) CLOCKTEXT3 {
    	if (SDLMediaClockFormat_CLOCKTEXT3 == nil) {
        		SDLMediaClockFormat_CLOCKTEXT3 = [[SDLMediaClockFormat alloc] initWithValue:@"CLOCKTEXT3"];
    	}
    	return SDLMediaClockFormat_CLOCKTEXT3;
}

@end
