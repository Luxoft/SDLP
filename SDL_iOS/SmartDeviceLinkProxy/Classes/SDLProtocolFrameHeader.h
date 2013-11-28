//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>

typedef enum SDLFrameType {
	SDLFrameType_Control = 0x00,
	SDLFrameType_Single = 0x01,
	SDLFrameType_First = 0x02,
	SDLFrameType_Consecutive = 0x03,
	
} SDLFrameType;

typedef enum SDLSessionType {
	SDLSessionType_RPC = 0x7,
	SDLSessionType_BulkData = 0xF,
} SDLSessionType;

typedef enum SDLFrameData {
	SDLFrameData_Heartbeat = 0x00,
	SDLFrameData_StartSession = 0x01,
	SDLFrameData_StartSessionACK = 0x02,
	SDLFrameData_StartSessionNACK = 0x03,
	SDLFrameData_EndSession = 0x04,
	
	SDLFrameData_SingleFrame = 0x00,
	SDLFrameData_FirstFrame = 0x00,
} SDLFrameData;

@interface SDLProtocolFrameHeader : NSObject {
	Byte version;
	BOOL compressed;
	SDLFrameType frameType;
	SDLSessionType sessionType;
	Byte frameData;
	Byte sessionID;
	
	UInt32 dataSize;
}

@property(assign) Byte version;
@property(assign) BOOL compressed;
@property(assign) SDLFrameType frameType;
@property(assign) SDLSessionType sessionType;
@property(assign) Byte frameData;
@property(assign) Byte sessionID;

@property(assign) UInt32 dataSize;

@end