//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLRegisterAppInterfaceResponse.h"
#import "SDLNames.h"

@implementation SDLRegisterAppInterfaceResponse

-(id) init {
    if (self = [super initWithName:NAMES_RegisterAppInterface]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setSyncMsgVersion:(SDLMsgVersion*) syncMsgVersion {
    if (syncMsgVersion != nil) {
        [parameters setObject:syncMsgVersion forKey:NAMES_syncMsgVersion];
    } else {
        [parameters removeObjectForKey:NAMES_syncMsgVersion];
    }
}

-(SDLMsgVersion*) syncMsgVersion {
    NSObject* obj = [parameters objectForKey:NAMES_syncMsgVersion];
    if ([obj isKindOfClass:SDLMsgVersion.class]) {
        return (SDLMsgVersion*)obj;
    } else {
        return [[[SDLMsgVersion alloc] initWithDictionary:(NSMutableDictionary*)obj] autorelease];
    }
}

-(void) setAutoActivateID:(NSString*) autoActivateID {
    if (autoActivateID != nil) {
        [parameters setObject:autoActivateID forKey:NAMES_autoActivateID];
    } else {
        [parameters removeObjectForKey:NAMES_autoActivateID];
    }
}

-(NSString*) autoActivateID {
    return [parameters objectForKey:NAMES_autoActivateID];
}

-(void) setLanguage:(SDLLanguage*) language {
    if (language != nil) {
        [parameters setObject:language forKey:NAMES_language];
    } else {
        [parameters removeObjectForKey:NAMES_language];
    }
}

-(SDLLanguage*) language {
    NSObject* obj = [parameters objectForKey:NAMES_language];
    if ([obj isKindOfClass:SDLLanguage.class]) {
        return (SDLLanguage*)obj;
    } else { 
        return [SDLLanguage valueOf:(NSString*)obj];
    }
}

-(void) setDisplayCapabilities:(SDLDisplayCapabilities*) displayCapabilities {
    if (displayCapabilities != nil) {
        [parameters setObject:displayCapabilities forKey:NAMES_displayCapabilities];
    } else {
        [parameters removeObjectForKey:NAMES_displayCapabilities];
    }
}

-(SDLDisplayCapabilities*) displayCapabilities {
    NSObject* obj = [parameters objectForKey:NAMES_displayCapabilities];
    if ([obj isKindOfClass:SDLDisplayCapabilities.class]) {
        return (SDLDisplayCapabilities*)obj;
    } else {
        return [[[SDLDisplayCapabilities alloc] initWithDictionary:(NSMutableDictionary*)obj] autorelease];
    }
}

-(void) setButtonCapabilities:(NSMutableArray*) buttonCapabilities {
    if (buttonCapabilities != nil) {
        [parameters setObject:buttonCapabilities forKey:NAMES_buttonCapabilities];
    } else {
        [parameters removeObjectForKey:NAMES_buttonCapabilities];
    }
}

-(NSMutableArray*) buttonCapabilities {
    NSMutableArray* array = [parameters objectForKey:NAMES_buttonCapabilities];
    if ([array count] < 1 || [[array objectAtIndex:0] isKindOfClass:SDLButtonCapabilities.class]) {
        return array;
    } else {
        NSMutableArray* newList = [NSMutableArray arrayWithCapacity:[array count]];
        for (NSDictionary* dict in array) {
            [newList addObject:[[[SDLButtonCapabilities alloc] initWithDictionary:(NSMutableDictionary*)dict] autorelease]];
        }
        return newList;
    }
}

-(void) setHmiZoneCapabilities:(NSMutableArray*) hmiZoneCapabilities {
    if (hmiZoneCapabilities != nil) {
        [parameters setObject:hmiZoneCapabilities forKey:NAMES_hmiZoneCapabilities];
    } else {
        [parameters removeObjectForKey:NAMES_hmiZoneCapabilities];
    }
}

-(NSMutableArray*) hmiZoneCapabilities {
    NSMutableArray* array = [parameters objectForKey:NAMES_hmiZoneCapabilities];
    if ([array count] < 1 || [[array objectAtIndex:0] isKindOfClass:SDLHMIZoneCapabilities.class]) {
        return array;
    } else { 
        NSMutableArray* newList = [NSMutableArray arrayWithCapacity:[array count]];
        for (NSString* enumString in array) {
            [newList addObject:[SDLHMIZoneCapabilities valueOf:enumString]];
        }
        return newList;
    }
}

-(void) setSpeechCapabilities:(NSMutableArray*) speechCapabilities {
    if (speechCapabilities != nil) {
        [parameters setObject:speechCapabilities forKey:NAMES_speechCapabilities];
    } else {
        [parameters removeObjectForKey:NAMES_speechCapabilities];
    }
}

-(NSMutableArray*) speechCapabilities {
    NSMutableArray* array = [parameters objectForKey:NAMES_speechCapabilities];
    if ([array count] < 1 || [[array objectAtIndex:0] isKindOfClass:SDLSpeechCapabilities.class]) {
        return array;
    } else { 
        NSMutableArray* newList = [NSMutableArray arrayWithCapacity:[array count]];
        for (NSString* enumString in array) {
            [newList addObject:[SDLSpeechCapabilities valueOf:enumString]];
        }
        return newList;
    }
}

-(void) setVrCapabilities:(NSMutableArray*) vrCapabilities {
    if (vrCapabilities != nil) {
        [parameters setObject:vrCapabilities forKey:NAMES_vrCapabilities];
    } else {
        [parameters removeObjectForKey:NAMES_vrCapabilities];
    }
}

-(NSMutableArray*) vrCapabilities {
    NSMutableArray* array = [parameters objectForKey:NAMES_vrCapabilities];
    if ([array count] < 1 || [[array objectAtIndex:0] isKindOfClass:SDLVRCapabilities.class]) {
        return array;
    } else { 
        NSMutableArray* newList = [NSMutableArray arrayWithCapacity:[array count]];
        for (NSString* enumString in array) {
            [newList addObject:[SDLVRCapabilities valueOf:enumString]];
        }
        return newList;
    }
}

@end
