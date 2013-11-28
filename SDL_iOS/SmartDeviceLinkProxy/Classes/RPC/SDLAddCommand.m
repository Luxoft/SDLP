//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLAddCommand.h"
#import "SDLNames.h"

@implementation SDLAddCommand

-(id) init {
    if (self = [super initWithName:NAMES_AddCommand]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setCmdID:(NSNumber*) cmdID {
    if (cmdID != nil) {
        [parameters setObject:cmdID forKey:NAMES_cmdID];
    } else {
        [parameters removeObjectForKey:NAMES_cmdID];
    }
}

-(NSNumber*) cmdID {
    return [parameters objectForKey:NAMES_cmdID];
}

-(void) setMenuParams:(SDLMenuParams*) menuParams {
    if (menuParams != nil) {
        [parameters setObject:menuParams forKey:NAMES_menuParams];
    } else {
        [parameters removeObjectForKey:NAMES_menuParams];
    }
}

-(SDLMenuParams*) menuParams {
    NSObject* obj = [parameters objectForKey:NAMES_menuParams];
    if ([obj isKindOfClass:SDLMenuParams.class]) {
        return (SDLMenuParams*)obj;
    } else {
        return [[[SDLMenuParams alloc] initWithDictionary:(NSMutableDictionary*)obj] autorelease];
    }
}

-(void) setVrCommands:(NSMutableArray*) vrCommands {
    if (vrCommands != nil) {
        [parameters setObject:vrCommands forKey:NAMES_vrCommands];
    } else {
        [parameters removeObjectForKey:NAMES_vrCommands];
    }
}

-(NSMutableArray*) vrCommands { 
    return [parameters objectForKey:NAMES_vrCommands];
}

@end
