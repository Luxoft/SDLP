//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLGlobalProperty.h"

SDLGlobalProperty* SDLGlobalProperty_HELPPROMPT = nil;
SDLGlobalProperty* SDLGlobalProperty_TIMEOUTPROMPT = nil;

NSMutableArray* SDLGlobalProperty_values = nil;
@implementation SDLGlobalProperty

+(SDLGlobalProperty*) valueOf:(NSString*) value {
    for (SDLGlobalProperty* item in SDLGlobalProperty.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLGlobalProperty_values == nil) {
        SDLGlobalProperty_values = [[NSMutableArray alloc] initWithObjects:
                SDLGlobalProperty.HELPPROMPT,
                SDLGlobalProperty.TIMEOUTPROMPT,
                nil];
    }
    return SDLGlobalProperty_values;
}

+(SDLGlobalProperty*) HELPPROMPT {
    	if (SDLGlobalProperty_HELPPROMPT == nil) {
        		SDLGlobalProperty_HELPPROMPT = [[SDLGlobalProperty alloc] initWithValue:@"HELPPROMPT"];
    	}
    	return SDLGlobalProperty_HELPPROMPT;
}

+(SDLGlobalProperty*) TIMEOUTPROMPT {
    	if (SDLGlobalProperty_TIMEOUTPROMPT == nil) {
        		SDLGlobalProperty_TIMEOUTPROMPT = [[SDLGlobalProperty alloc] initWithValue:@"TIMEOUTPROMPT"];
    	}
    	return SDLGlobalProperty_TIMEOUTPROMPT;
}

@end
