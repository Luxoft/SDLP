//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLUpdateMode.h"

SDLUpdateMode* SDLUpdateMode_COUNTUP = nil;
SDLUpdateMode* SDLUpdateMode_COUNTDOWN = nil;
SDLUpdateMode* SDLUpdateMode_PAUSE = nil;
SDLUpdateMode* SDLUpdateMode_RESUME = nil;

NSMutableArray* SDLUpdateMode_values = nil;
@implementation SDLUpdateMode

+(SDLUpdateMode*) valueOf:(NSString*) value {
    for (SDLUpdateMode* item in SDLUpdateMode.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLUpdateMode_values == nil) {
        SDLUpdateMode_values = [[NSMutableArray alloc] initWithObjects:
                SDLUpdateMode.COUNTUP,
                SDLUpdateMode.COUNTDOWN,
                SDLUpdateMode.PAUSE,
                SDLUpdateMode.RESUME,
                nil];
    }
    return SDLUpdateMode_values;
}

+(SDLUpdateMode*) COUNTUP {
    	if (SDLUpdateMode_COUNTUP == nil) {
        		SDLUpdateMode_COUNTUP = [[SDLUpdateMode alloc] initWithValue:@"COUNTUP"];
    	}
    	return SDLUpdateMode_COUNTUP;
}

+(SDLUpdateMode*) COUNTDOWN {
    	if (SDLUpdateMode_COUNTDOWN == nil) {
        		SDLUpdateMode_COUNTDOWN = [[SDLUpdateMode alloc] initWithValue:@"COUNTDOWN"];
    	}
    	return SDLUpdateMode_COUNTDOWN;
}

+(SDLUpdateMode*) PAUSE {
    	if (SDLUpdateMode_PAUSE == nil) {
        		SDLUpdateMode_PAUSE = [[SDLUpdateMode alloc] initWithValue:@"PAUSE"];
    	}
    	return SDLUpdateMode_PAUSE;
}

+(SDLUpdateMode*) RESUME {
    	if (SDLUpdateMode_RESUME == nil) {
        		SDLUpdateMode_RESUME = [[SDLUpdateMode alloc] initWithValue:@"RESUME"];
    	}
    	return SDLUpdateMode_RESUME;
}

@end
