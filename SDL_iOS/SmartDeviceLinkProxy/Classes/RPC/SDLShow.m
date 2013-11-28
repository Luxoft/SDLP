//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLShow.h"
#import "SDLNames.h"

@implementation SDLShow

-(id) init {
    if (self = [super initWithName:NAMES_Show]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setMainField1:(NSString*) mainField1 {
    if (mainField1 != nil) {
        [parameters setObject:mainField1 forKey:NAMES_mainField1];
    } else {
        [parameters removeObjectForKey:NAMES_mainField1];
    }
}

-(NSString*) mainField1 {
    return [parameters objectForKey:NAMES_mainField1];
}

-(void) setMainField2:(NSString*) mainField2 {
    if (mainField2 != nil) {
        [parameters setObject:mainField2 forKey:NAMES_mainField2];
    } else {
        [parameters removeObjectForKey:NAMES_mainField2];
    }
}

-(NSString*) mainField2 {
    return [parameters objectForKey:NAMES_mainField2];
}

-(void) setAlignment:(SDLTextAlignment*) alignment {
    if (alignment != nil) {
        [parameters setObject:alignment forKey:NAMES_alignment];
    } else {
        [parameters removeObjectForKey:NAMES_alignment];
    }
}

-(SDLTextAlignment*) alignment {
    NSObject* obj = [parameters objectForKey:NAMES_alignment];
    if ([obj isKindOfClass:SDLTextAlignment.class]) {
        return (SDLTextAlignment*)obj;
    } else { 
        return [SDLTextAlignment valueOf:(NSString*)obj];
    }
}

-(void) setStatusBar:(NSString*) statusBar {
    if (statusBar != nil) {
        [parameters setObject:statusBar forKey:NAMES_statusBar];
    } else {
        [parameters removeObjectForKey:NAMES_statusBar];
    }
}

-(NSString*) statusBar {
    return [parameters objectForKey:NAMES_statusBar];
}

-(void) setMediaClock:(NSString*) mediaClock {
    if (mediaClock != nil) {
        [parameters setObject:mediaClock forKey:NAMES_mediaClock];
    } else {
        [parameters removeObjectForKey:NAMES_mediaClock];
    }
}

-(NSString*) mediaClock {
    return [parameters objectForKey:NAMES_mediaClock];
}

-(void) setMediaTrack:(NSString*) mediaTrack {
    if (mediaTrack != nil) {
        [parameters setObject:mediaTrack forKey:NAMES_mediaTrack];
    } else {
        [parameters removeObjectForKey:NAMES_mediaTrack];
    }
}

-(NSString*) mediaTrack {
    return [parameters objectForKey:NAMES_mediaTrack];
}

@end
