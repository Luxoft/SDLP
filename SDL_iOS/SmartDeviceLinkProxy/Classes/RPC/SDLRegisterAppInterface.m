//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLRegisterAppInterface.h"
#import "SDLNames.h"

@implementation SDLRegisterAppInterface

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

-(void) setAppName:(NSString*) appName {
    if (appName != nil) {
        [parameters setObject:appName forKey:NAMES_appName];
    } else {
        [parameters removeObjectForKey:NAMES_appName];
    }
}

-(NSString*) appName {
    return [parameters objectForKey:NAMES_appName];
}

-(void) setNgnMediaScreenAppName:(NSString*) ngnMediaScreenAppName {
    if (ngnMediaScreenAppName != nil) {
        [parameters setObject:ngnMediaScreenAppName forKey:NAMES_ngnMediaScreenAppName];
    } else {
        [parameters removeObjectForKey:NAMES_ngnMediaScreenAppName];
    }
}

-(NSString*) ngnMediaScreenAppName {
    return [parameters objectForKey:NAMES_ngnMediaScreenAppName];
}

-(void) setVrSynonyms:(NSMutableArray*) vrSynonyms {
    if (vrSynonyms != nil) {
        [parameters setObject:vrSynonyms forKey:NAMES_vrSynonyms];
    } else {
        [parameters removeObjectForKey:NAMES_vrSynonyms];
    }
}

-(NSMutableArray*) vrSynonyms { 
    return [parameters objectForKey:NAMES_vrSynonyms];
}

-(void) setIsMediaApplication:(NSNumber*) isMediaApplication {
    if (isMediaApplication != nil) {
        [parameters setObject:isMediaApplication forKey:NAMES_isMediaApplication];
    } else {
        [parameters removeObjectForKey:NAMES_isMediaApplication];
    }
}

-(NSNumber*) isMediaApplication {
    return [parameters objectForKey:NAMES_isMediaApplication];
}

-(void) setLanguageDesired:(SDLLanguage*) languageDesired {
    if (languageDesired != nil) {
        [parameters setObject:languageDesired forKey:NAMES_languageDesired];
    } else {
        [parameters removeObjectForKey:NAMES_languageDesired];
    }
}

-(SDLLanguage*) languageDesired {
    NSObject* obj = [parameters objectForKey:NAMES_languageDesired];
    if ([obj isKindOfClass:SDLLanguage.class]) {
        return (SDLLanguage*)obj;
    } else { 
        return [SDLLanguage valueOf:(NSString*)obj];
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

@end
