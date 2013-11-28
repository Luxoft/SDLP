//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLProtocolFrameHeaderFactory.h"
#import "SDLBitConverter.h"

@implementation SDLProtocolFrameHeaderFactory

+(SDLProtocolFrameHeader*) parseHeader:(NSData*) header {
	SDLProtocolFrameHeader* msg = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	
	Byte version = (Byte)(((Byte*)header.bytes)[0] >> 4);
	BOOL compressed = (1 == ((((Byte*)header.bytes)[0] & 0x08) >> 3));
	Byte frameType = (Byte)(((Byte*)header.bytes)[0] & 0x07);
	Byte sessionType = ((Byte*)header.bytes)[1];
	Byte frameData = ((Byte*)header.bytes)[2];
	Byte sessionID = ((Byte*)header.bytes)[3];
	UInt32 dataSize = [SDLBitConverter intFromByteArray:((Byte*)header.bytes) offset:4];
	
	msg.version = version;
	msg.compressed = compressed;
	msg.frameType = frameType;
	msg.sessionType = sessionType;
	msg.frameData = frameData;
	msg.sessionID = sessionID;
	msg.dataSize = dataSize;
	
	return msg;
}

+(SDLProtocolFrameHeader*) startSessionWithSessionType:(SDLSessionType) sessionType {
	SDLProtocolFrameHeader* msg = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	msg.frameType = SDLFrameType_Control;
	msg.sessionType = sessionType;
	msg.frameData = SDLFrameData_StartSession;
	
	return msg;
}


+(SDLProtocolFrameHeader*) endSessionWithSessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID {
	SDLProtocolFrameHeader* header = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	header.frameType = SDLFrameType_Control;
	header.frameData = SDLFrameData_EndSession;
	header.sessionType = sessionType;
	header.sessionID = sessionID;

	return header;
}
+(SDLProtocolFrameHeader*) singleFrameWithSessionType:(SDLSessionType) sessionType sessionID:(Byte) sessionID dataSize:(NSInteger) dataSize {
	SDLProtocolFrameHeader* header = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	header.frameType = SDLFrameType_Single;
	header.sessionType = sessionType;
	header.sessionID = sessionID;
	header.dataSize = dataSize;
	
	return header;
}

+(SDLProtocolFrameHeader*) firstFrameWithSessionType:(SDLSessionType) sessionType sessionID:(Byte) sessionID{
	SDLProtocolFrameHeader* header = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	header.frameType = SDLFrameType_First;
	header.sessionType = sessionType;
	header.sessionID = sessionID;
	header.dataSize = 8;
	
	return header;
}

+(SDLProtocolFrameHeader*) consecutiveFrameWithSessionType:(SDLSessionType) sessionType sessionID:(Byte) sessionID dataSize:(NSInteger) dataSize {
	SDLProtocolFrameHeader* header = [[[SDLProtocolFrameHeader alloc] init] autorelease];
	header.frameType = SDLFrameType_Consecutive;
	header.sessionType = sessionType;
	header.sessionID = sessionID;
	header.dataSize = dataSize;
	
	return header;
}

@end
