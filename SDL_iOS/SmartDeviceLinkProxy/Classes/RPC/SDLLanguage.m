//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLLanguage.h"

SDLLanguage* SDLLanguage_EN_US = nil;
SDLLanguage* SDLLanguage_ES_MX = nil;
SDLLanguage* SDLLanguage_FR_CA = nil;

NSMutableArray* SDLLanguage_values = nil;
@implementation SDLLanguage

+(SDLLanguage*) valueOf:(NSString*) value {
    for (SDLLanguage* item in SDLLanguage.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLLanguage_values == nil) {
        SDLLanguage_values = [[NSMutableArray alloc] initWithObjects:
                SDLLanguage.EN_US,
                SDLLanguage.ES_MX,
                SDLLanguage.FR_CA,
                nil];
    }
    return SDLLanguage_values;
}

+(SDLLanguage*) EN_US {
    	if (SDLLanguage_EN_US == nil) {
        		SDLLanguage_EN_US = [[SDLLanguage alloc] initWithValue:@"EN-US"];
    	}
    	return SDLLanguage_EN_US;
}

+(SDLLanguage*) ES_MX {
    	if (SDLLanguage_ES_MX == nil) {
        		SDLLanguage_ES_MX = [[SDLLanguage alloc] initWithValue:@"ES-MX"];
    	}
    	return SDLLanguage_ES_MX;
}

+(SDLLanguage*) FR_CA {
    	if (SDLLanguage_FR_CA == nil) {
        		SDLLanguage_FR_CA = [[SDLLanguage alloc] initWithValue:@"FR-CA"];
    	}
    	return SDLLanguage_FR_CA;
}

@end
