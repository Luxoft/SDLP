//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLProtocolMessage.h"

@implementation SDLProtocolMessage

@synthesize messageType;
@synthesize sessionType;
@synthesize sessionID;
@synthesize data;

-(id) init {
	if (self = [super init]) {
		messageType = SDLMessageType_Data;
		sessionType = SDLSessionType_RPC;
		sessionID = 0;
		data = nil;
	}
	return self;
}

-(void) dealloc {
    [data release];
    [super dealloc];
}
				
@end
