//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLProtocolFrameHeader.h"

typedef enum SDLMessageType {
	SDLMessageType_StartSession = 0x01,
	SDLMessageType_StartSessionACK = 0x02,
	SDLMessageType_StartSessionNACK = 0x03,
	SDLMessageType_EndSession = 0x04,
	
	SDLMessageType_Data = 0x05
} SDLMessageType;

@interface SDLProtocolMessage : NSObject {
	SDLMessageType messageType;
	SDLSessionType sessionType;
	Byte sessionID;
	
	NSData* data;
}

@property(assign) SDLMessageType messageType;
@property(assign) SDLSessionType sessionType;
@property(assign) Byte sessionID;

@property(retain) NSData* data;

@end