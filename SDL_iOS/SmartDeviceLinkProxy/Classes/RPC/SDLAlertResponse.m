//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLAlertResponse.h"
#import "SDLNames.h"

@implementation SDLAlertResponse

-(id) init {
    if (self = [super initWithName:NAMES_Alert]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

@end
