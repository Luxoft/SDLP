//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLProtocol.h"
#import "SDLBitConverter.h"
#import "SDLDebugTool.h"
#import "SDLProtocolFrameHeaderFactory.h"
#import <UIKit/UIKit.h>

#define HEADER_BUF_LENGTH 8
#define MTU_SIZE 512

@implementation SDLProtocol

-(id) init {
	if (self = [super init]) {
		msgLock = [[NSObject alloc] init];
		headerBuf = nil;
		dataBuf = nil;
		currentHeader = nil;
		[self resetHeaderAndData];
		frameAssemblerForSessionID = [[NSMutableDictionary alloc] initWithCapacity:2];
	}
	return self;
}

-(void) resetHeaderAndData {
    [headerBuf release];

	haveHeader = NO;
	int headerSize = HEADER_BUF_LENGTH * sizeof(Byte);
	headerBuf = [[NSMutableData alloc] initWithCapacity:headerSize];	

    [dataBuf release];
    dataBuf = nil;

    [currentHeader release];
    currentHeader = nil;
}


- (void) doAlertMessage:(NSString*) message withTitle:(NSString*) title{
	UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alertView show];
	[alertView release];
	
}//end action

-(FrameAssembler*) getFrameAssemblerForFrameHeader:(SDLProtocolFrameHeader*) header {
	id sessionIDKey = [NSNumber numberWithInt:header.sessionID];
    
	FrameAssembler *ret = [frameAssemblerForSessionID objectForKey:sessionIDKey];

	if (ret == nil) {
		if (header.sessionType == SDLSessionType_RPC) {
			ret = [[FrameAssembler alloc] initWithListeners:protocolListeners];
		} else if (header.sessionType == SDLSessionType_BulkData) {
			ret = [[BulkAssembler alloc] initWithListeners:protocolListeners];
		}
        
		[frameAssemblerForSessionID setObject:ret forKey:sessionIDKey];
        return [ret autorelease];
	}
	return ret;
}

-(void) handleBytesFromTransport:(Byte *)receivedBytes length:(long)receivedBytesLength {
	long receivedBytesReadPos = 0;
	// If I don't yet know the message size, grab those bytes.
	if (!haveHeader) {
		// If I can't get the size, just get the bytes that are there.
		int sizeBytesNeeded = HEADER_BUF_LENGTH - headerBuf.length;
		if (receivedBytesLength < sizeBytesNeeded) {
			[headerBuf appendBytes:receivedBytes + receivedBytesReadPos length:receivedBytesLength];
			return;
		} else {
            // If I got the size, allocate the buffer
			[headerBuf appendBytes:receivedBytes + receivedBytesReadPos length:sizeBytesNeeded];
			receivedBytesReadPos += sizeBytesNeeded;
			haveHeader = true;
			dataBufFinalLength = [SDLBitConverter intFromByteArray:(Byte*)headerBuf.bytes offset:4];
            
            [dataBuf release];
            dataBuf = nil;

			dataBuf = [[NSMutableData alloc] initWithCapacity:dataBufFinalLength];
			currentHeader = [[SDLProtocolFrameHeaderFactory parseHeader:headerBuf] retain];
		}
		
	}
	
	int bytesLeft = receivedBytesLength - receivedBytesReadPos;
	int bytesNeeded = dataBufFinalLength - dataBuf.length;
	// If I don't have enough bytes for the message, just grab what's there.
	if (bytesLeft < bytesNeeded) {
		[dataBuf appendBytes:receivedBytes + receivedBytesReadPos length:bytesLeft];
		return;
	} else {
        // Fill the buffer and call the handler!
		[dataBuf appendBytes:receivedBytes + receivedBytesReadPos length:bytesNeeded];
		receivedBytesReadPos += bytesNeeded;
		FrameAssembler *assembler = [self getFrameAssemblerForFrameHeader:currentHeader];
		[assembler handleFrame:currentHeader data:dataBuf];
		[self resetHeaderAndData];
		
		//If there are any bytes left, recurse.
		int moreBytesLeft = receivedBytesLength - receivedBytesReadPos;
		if (moreBytesLeft > 0) {
			[self handleBytesFromTransport:receivedBytes + receivedBytesReadPos  length:moreBytesLeft];
		}
	}
}

-(NSData*) assembleHeaderBytes:(SDLProtocolFrameHeader*) msg {
	UInt32 header = 0;
	header |= msg.version;
	header <<= 1;
	header |= (msg.compressed ? 1 : 0);
	header <<= 3;
	header |= msg.frameType;
	header <<= 8;
	header |= msg.sessionType;
	header <<= 8;
	header |= msg.frameData;
	header <<= 8;
	header |= msg.sessionID;
	
	Byte* mallocPtr = malloc(HEADER_BUF_LENGTH);
	if (mallocPtr == nil) {
		@throw [NSException exceptionWithName:@"OutOfMemoryException" reason:@"malloc failed" userInfo:nil];
	}
	NSData* ret = [[NSData alloc] initWithBytesNoCopy:mallocPtr length:HEADER_BUF_LENGTH];

	memcpy((void*)ret.bytes, [SDLBitConverter intToByteArray:header].bytes, 4);
	memcpy((void*)ret.bytes + 4, [SDLBitConverter intToByteArray:msg.dataSize].bytes, 4);
	
	return [ret autorelease];
}

-(void) sendFrameToTransport:(SDLProtocolFrameHeader *)header withData:(NSData*) data {
	if (data == nil || data.length == 0){
		[transport sendBytes:[self assembleHeaderBytes:header]];
	} else {
		NSMutableData* toSend = [NSMutableData dataWithCapacity:data.length + HEADER_BUF_LENGTH];
		
		[toSend appendData:[self assembleHeaderBytes:header]];
		
		[toSend appendData:data];
		
		[transport sendBytes:toSend];
	}
	
}

-(void) sendFrameToTransport:(SDLProtocolFrameHeader *)header {
	[self sendFrameToTransport:header withData:nil];
}

-(void) sendFrameToTransport:(SDLProtocolFrameHeader *)header withData:(NSData*) data offset:(NSInteger) offset length:(NSInteger) length{
	
	NSMutableData* toSend = [NSMutableData dataWithCapacity:length + HEADER_BUF_LENGTH];
	
	[toSend appendData:[self assembleHeaderBytes:header]];
	
	[toSend appendBytes:data.bytes + offset length:length];
	
	[transport sendBytes:toSend];
	
}

-(void) sendData:(NSData*)data sessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID {
	int maxDataSize = MTU_SIZE - HEADER_BUF_LENGTH;
	
	@synchronized (msgLock) {
        if (data.length < maxDataSize) {
            
            SDLProtocolFrameHeader *singleHeader = [SDLProtocolFrameHeaderFactory singleFrameWithSessionType:sessionType sessionID:sessionID dataSize:data.length];
            
            [self sendFrameToTransport:singleHeader withData:data];
        } else {
            SDLProtocolFrameHeader *firstHeader = [SDLProtocolFrameHeaderFactory firstFrameWithSessionType:sessionType sessionID:sessionID];
            
            // Assemble first frame.
            int frameCount = data.length / maxDataSize;
            if (data.length % maxDataSize > 0) {
                frameCount++;
            }
            NSMutableData *firstFrameData = [NSMutableData dataWithCapacity:8];
            // First four bytes are data size.
            [firstFrameData appendData:[SDLBitConverter intToByteArray:data.length]];
            // Second four bytes are frame count.
            [firstFrameData appendData:[SDLBitConverter intToByteArray:frameCount]];
            
            [self sendFrameToTransport:firstHeader withData:firstFrameData];
            
            int currentOffset = 0;
            
            for (int i = 0; i < frameCount; i++) {
                int bytesToWrite = data.length - currentOffset;
                if (bytesToWrite > maxDataSize) { bytesToWrite = maxDataSize
                    ; }
                SDLProtocolFrameHeader *consecHeader = [SDLProtocolFrameHeaderFactory consecutiveFrameWithSessionType:sessionType sessionID:sessionID dataSize:bytesToWrite];
                if (i != frameCount - 1) {
                    [consecHeader setFrameData: 1];
                }
                [self sendFrameToTransport:consecHeader withData:data offset:currentOffset length:bytesToWrite];
                currentOffset += bytesToWrite;
                
            }
        }
		
	}
}


-(void) sendStartSessionWithType:(SDLSessionType) sessionType {
	SDLProtocolFrameHeader *header = [SDLProtocolFrameHeaderFactory startSessionWithSessionType:sessionType];
	
	@synchronized (msgLock) {
		[self sendFrameToTransport:header];
	}
}

-(void) sendEndSessionWithType:(SDLSessionType)sessionType sessionID:(Byte)sessionID {
	SDLProtocolFrameHeader *header = [SDLProtocolFrameHeaderFactory endSessionWithSessionType:sessionType sessionID:sessionID];
	@synchronized (msgLock) {
		[self sendFrameToTransport:header];
	}
}


-(void) dealloc {

    [headerBuf release];
    headerBuf = nil;

    [dataBuf release];
    dataBuf = nil;

    [currentHeader release];
    currentHeader = nil;

    [frameAssemblerForSessionID release];
    frameAssemblerForSessionID = nil;

    [msgLock release];
    msgLock = nil;
	
	[super dealloc];
}

@end

@implementation FrameAssembler

-(id) initWithListeners:(NSArray*)theListeners{
	if (self = [super init]) {
		listeners = [theListeners retain];
	}
	return self;
}

-(void) handleFirstFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	//The message is new, so let's figure out how big it is.
	hasFirstFrame = true;
	totalSize = [SDLBitConverter intFromByteArray:(Byte*)data.bytes offset:0] - 8;
	framesRemaining = [SDLBitConverter intFromByteArray:(Byte*)data.bytes offset:4];
    
    [accumulator release];
    accumulator = nil;
    
	accumulator = [[NSMutableData dataWithCapacity:totalSize] retain];
	
}

-(void) handleSecondFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	[self handleRemainingFrame:header data:data];
}

-(void) handleRemainingFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	[accumulator appendData:data];
	[self notifyIfFinished:header];
	
}

-(void) notifyIfFinished:(SDLProtocolFrameHeader*) header {
	if (framesRemaining == 0) {
		SDLProtocolMessage *message = [[SDLProtocolMessage alloc] init];
		message.messageType = SDLMessageType_Data;
		message.sessionType = header.sessionType;
		message.sessionID = header.sessionID;
		message.data = accumulator;
		
		NSArray* localListeners = nil;
		@synchronized (listeners) {
			localListeners = [listeners copy];
		}
			
		for (NSObject<SDLProtocolListener> *listener in localListeners) {
			[listener onProtocolMessageReceived:message];
		}
		[localListeners release];
        
        [message release];
		
		hasFirstFrame = false;
		hasSecondFrame = false;

        [accumulator release];
        accumulator = nil;

	}
}

-(void) handleMultiFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	if (!hasFirstFrame) {
		hasFirstFrame = true;
		[self handleFirstFrame:header data:data];
	} else if (!hasSecondFrame) {
		hasSecondFrame = true;
		framesRemaining--;
		[self handleSecondFrame:header data:data ];
	} else {
		framesRemaining--;
		[self handleRemainingFrame:header data:data];
	}
	
}

-(void) handleFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	if (header.frameType == SDLFrameType_First || header.frameType == SDLFrameType_Consecutive) {
		[self handleMultiFrame:header data:data];
	} else {
		SDLProtocolMessage *message = [[SDLProtocolMessage alloc] init];
		message.messageType = [self messageTypeForFrameHeader:header];
		message.sessionType = header.sessionType;
		message.sessionID = header.sessionID;
		message.data = data;
		
		NSArray* localListeners = nil;
		@synchronized (listeners) {
			localListeners = [listeners copy];
		}
		
		for (NSObject<SDLProtocolListener> *listener in localListeners) {
			[listener onProtocolMessageReceived:message];
		}
		[localListeners release];
        
        [message release];
	}
}
	
-(SDLMessageType) messageTypeForFrameHeader:(SDLProtocolFrameHeader*)header {
	if (header.frameType == SDLFrameType_Control) {
		if (header.frameData == SDLFrameData_StartSession) {
			return SDLMessageType_StartSession;
		} else if (header.frameData == SDLFrameData_StartSessionACK) {
			return SDLMessageType_StartSessionACK;
		} else if (header.frameData == SDLFrameData_StartSessionNACK) {
			return SDLMessageType_StartSessionNACK;
		} else {
            //if (frameData == FrameData.EndSession.value())
			return SDLMessageType_EndSession;
		}
	} else {
		return SDLMessageType_Data;
	}
}

-(void) dealloc {

    [accumulator release];
    accumulator = nil;
    
    [listeners release];
    listeners = nil;
    
    [super dealloc];
}

@end

@implementation BulkAssembler

-(void) handleSecondFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data {
	bulkCorrId = [SDLBitConverter intFromByteArray:(Byte*)data.bytes offset:4];
	[accumulator appendBytes:data.bytes + 8 length:header.dataSize - 8];
	[self notifyIfFinished:header];
}

@end


