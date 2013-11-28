//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLSystemContext.h"

SDLSystemContext* SDLSystemContext_SYSCTXT_MAIN = nil;
SDLSystemContext* SDLSystemContext_SYSCTXT_VRSESSION = nil;
SDLSystemContext* SDLSystemContext_SYSCTXT_MENU = nil;

NSMutableArray* SDLSystemContext_values = nil;
@implementation SDLSystemContext

+(SDLSystemContext*) valueOf:(NSString*) value {
    for (SDLSystemContext* item in SDLSystemContext.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLSystemContext_values == nil) {
        SDLSystemContext_values = [[NSMutableArray alloc] initWithObjects:
                SDLSystemContext.SYSCTXT_MAIN,
                SDLSystemContext.SYSCTXT_VRSESSION,
                SDLSystemContext.SYSCTXT_MENU,
                nil];
    }
    return SDLSystemContext_values;
}

+(SDLSystemContext*) SYSCTXT_MAIN {
    	if (SDLSystemContext_SYSCTXT_MAIN == nil) {
        		SDLSystemContext_SYSCTXT_MAIN = [[SDLSystemContext alloc] initWithValue:@"MAIN"];
    	}
    	return SDLSystemContext_SYSCTXT_MAIN;
}

+(SDLSystemContext*) SYSCTXT_VRSESSION {
    	if (SDLSystemContext_SYSCTXT_VRSESSION == nil) {
        		SDLSystemContext_SYSCTXT_VRSESSION = [[SDLSystemContext alloc] initWithValue:@"VRSESSION"];
    	}
    	return SDLSystemContext_SYSCTXT_VRSESSION;
}

+(SDLSystemContext*) SYSCTXT_MENU {
    	if (SDLSystemContext_SYSCTXT_MENU == nil) {
        		SDLSystemContext_SYSCTXT_MENU = [[SDLSystemContext alloc] initWithValue:@"MENU"];
    	}
    	return SDLSystemContext_SYSCTXT_MENU;
}

@end
