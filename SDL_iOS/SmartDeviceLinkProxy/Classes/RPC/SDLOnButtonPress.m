//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLOnButtonPress.h"
#import "SDLNames.h"

@implementation SDLOnButtonPress

-(id) init {
    if (self = [super initWithName:NAMES_OnButtonPress]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setButtonName:(SDLButtonName*) buttonName {
    if (buttonName != nil) {
        [parameters setObject:buttonName forKey:NAMES_buttonName];
    } else {
        [parameters removeObjectForKey:NAMES_buttonName];
    }
}

-(SDLButtonName*) buttonName {
    NSObject* obj = [parameters objectForKey:NAMES_buttonName];
    if ([obj isKindOfClass:SDLButtonName.class]) {
        return (SDLButtonName*)obj;
    } else { 
        return [SDLButtonName valueOf:(NSString*)obj];
    }
}

-(void) setButtonPressMode:(SDLButtonPressMode*) buttonPressMode {
    if (buttonPressMode != nil) {
        [parameters setObject:buttonPressMode forKey:NAMES_buttonPressMode];
    } else {
        [parameters removeObjectForKey:NAMES_buttonPressMode];
    }
}

-(SDLButtonPressMode*) buttonPressMode {
    NSObject* obj = [parameters objectForKey:NAMES_buttonPressMode];
    if ([obj isKindOfClass:SDLButtonPressMode.class]) {
        return (SDLButtonPressMode*)obj;
    } else { 
        return [SDLButtonPressMode valueOf:(NSString*)obj];
    }
}

@end
