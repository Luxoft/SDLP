//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLVRCapabilities.h"

SDLVRCapabilities* SDLVRCapabilities_Text = nil;

NSMutableArray* SDLVRCapabilities_values = nil;
@implementation SDLVRCapabilities

+(SDLVRCapabilities*) valueOf:(NSString*) value {
    for (SDLVRCapabilities* item in SDLVRCapabilities.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLVRCapabilities_values == nil) {
        SDLVRCapabilities_values = [[NSMutableArray alloc] initWithObjects:
                SDLVRCapabilities.Text,
                nil];
    }
    return SDLVRCapabilities_values;
}

+(SDLVRCapabilities*) Text {
    	if (SDLVRCapabilities_Text == nil) {
        		SDLVRCapabilities_Text = [[SDLVRCapabilities alloc] initWithValue:@"Text"];
    	}
    	return SDLVRCapabilities_Text;
}

@end
