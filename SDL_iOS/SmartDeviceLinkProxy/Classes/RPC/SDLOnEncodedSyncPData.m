//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLOnEncodedSyncPData.h"
#import "SDLNames.h"

@implementation SDLOnEncodedSyncPData

-(id) init {
    if (self = [super initWithName:NAMES_OnEncodedSyncPData]) {}
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    if (self = [super initWithDictionary:dict]) {}
    return self;
}

-(void) setData:(NSMutableArray*) data {
    if (data != nil) {
        [parameters setObject:data forKey:NAMES_data];
    } else {
        [parameters removeObjectForKey:NAMES_data];
    }
}

-(NSMutableArray*) data {
    NSMutableArray* obj = [parameters objectForKey:NAMES_data];
	return (NSMutableArray*)obj;
}

@end
