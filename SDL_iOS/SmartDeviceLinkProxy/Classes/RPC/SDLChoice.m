//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLChoice.h"
#import "SDLNames.h"

@implementation SDLChoice

-(id) init {
    if (self = [super init]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setChoiceID:(NSNumber*) choiceID {
    if (choiceID != nil) {
        [store setObject:choiceID forKey:NAMES_choiceID];
    } else {
        [store removeObjectForKey:NAMES_choiceID];
    }
}

-(NSNumber*) choiceID {
    return [store objectForKey:NAMES_choiceID];
}

-(void) setMenuName:(NSString*) menuName {
    if (menuName != nil) {
        [store setObject:menuName forKey:NAMES_menuName];
    } else {
        [store removeObjectForKey:NAMES_menuName];
    }
}

-(NSString*) menuName {
    return [store objectForKey:NAMES_menuName];
}

-(void) setVrCommands:(NSMutableArray*) vrCommands {
    if (vrCommands != nil) {
        [store setObject:vrCommands forKey:NAMES_vrCommands];
    } else {
        [store removeObjectForKey:NAMES_vrCommands];
    }
}

-(NSMutableArray*) vrCommands { 
    return [store objectForKey:NAMES_vrCommands];
}

@end
