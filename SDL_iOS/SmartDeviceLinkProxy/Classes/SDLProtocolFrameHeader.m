//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLProtocolMessage.h"

@implementation SDLProtocolFrameHeader

@synthesize version;
@synthesize compressed;
@synthesize frameType;
@synthesize sessionType;
@synthesize frameData;
@synthesize sessionID;
@synthesize dataSize;

-(id) init {
	if (self = [super init]) {
		version = 1;
		compressed = false;
		frameType = SDLFrameType_Control;
		sessionType = SDLSessionType_RPC;
		frameData = 0;
		sessionID = 0;
		
		dataSize = 0;
	}
	return self;
}
				
@end
