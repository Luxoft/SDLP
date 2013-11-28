//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLTextFieldName.h"

SDLTextFieldName* SDLTextFieldName_mainField1 = nil;
SDLTextFieldName* SDLTextFieldName_mainField2 = nil;
SDLTextFieldName* SDLTextFieldName_statusBar = nil;
SDLTextFieldName* SDLTextFieldName_mediaClock = nil;
SDLTextFieldName* SDLTextFieldName_mediaTrack = nil;
SDLTextFieldName* SDLTextFieldName_alertText1 = nil;
SDLTextFieldName* SDLTextFieldName_alertText2 = nil;

NSMutableArray* SDLTextFieldName_values = nil;
@implementation SDLTextFieldName

+(SDLTextFieldName*) valueOf:(NSString*) value {
    for (SDLTextFieldName* item in SDLTextFieldName.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLTextFieldName_values == nil) {
        SDLTextFieldName_values = [[NSMutableArray alloc] initWithObjects:
                SDLTextFieldName.mainField1,
                SDLTextFieldName.mainField2,
                SDLTextFieldName.statusBar,
                SDLTextFieldName.mediaClock,
                SDLTextFieldName.mediaTrack,
                SDLTextFieldName.alertText1,
                SDLTextFieldName.alertText2,
                nil];
    }
    return SDLTextFieldName_values;
}

+(SDLTextFieldName*) mainField1 {
    	if (SDLTextFieldName_mainField1 == nil) {
        		SDLTextFieldName_mainField1 = [[SDLTextFieldName alloc] initWithValue:@"mainField1"];
    	}
    	return SDLTextFieldName_mainField1;
}

+(SDLTextFieldName*) mainField2 {
    	if (SDLTextFieldName_mainField2 == nil) {
        		SDLTextFieldName_mainField2 = [[SDLTextFieldName alloc] initWithValue:@"mainField2"];
    	}
    	return SDLTextFieldName_mainField2;
}

+(SDLTextFieldName*) statusBar {
    	if (SDLTextFieldName_statusBar == nil) {
        		SDLTextFieldName_statusBar = [[SDLTextFieldName alloc] initWithValue:@"statusBar"];
    	}
    	return SDLTextFieldName_statusBar;
}

+(SDLTextFieldName*) mediaClock {
    	if (SDLTextFieldName_mediaClock == nil) {
        		SDLTextFieldName_mediaClock = [[SDLTextFieldName alloc] initWithValue:@"mediaClock"];
    	}
    	return SDLTextFieldName_mediaClock;
}

+(SDLTextFieldName*) mediaTrack {
    	if (SDLTextFieldName_mediaTrack == nil) {
        		SDLTextFieldName_mediaTrack = [[SDLTextFieldName alloc] initWithValue:@"mediaTrack"];
    	}
    	return SDLTextFieldName_mediaTrack;
}

+(SDLTextFieldName*) alertText1 {
    	if (SDLTextFieldName_alertText1 == nil) {
        		SDLTextFieldName_alertText1 = [[SDLTextFieldName alloc] initWithValue:@"alertText1"];
    	}
    	return SDLTextFieldName_alertText1;
}

+(SDLTextFieldName*) alertText2 {
    	if (SDLTextFieldName_alertText2 == nil) {
        		SDLTextFieldName_alertText2 = [[SDLTextFieldName alloc] initWithValue:@"alertText2"];
    	}
    	return SDLTextFieldName_alertText2;
}

@end
