//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCNotification.h"

@interface SDLOnEncodedSyncPData: SDLRPCNotification {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSMutableArray* data;

@end