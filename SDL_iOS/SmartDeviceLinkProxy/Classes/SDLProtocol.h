//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLAbstractProtocol.h"

@interface SDLProtocol : SDLAbstractProtocol {
	BOOL haveHeader;
	NSMutableData* headerBuf;
	NSMutableData* dataBuf;
	SDLProtocolFrameHeader* currentHeader;
	NSMutableDictionary *frameAssemblerForSessionID;
	NSInteger dataBufFinalLength;
	NSObject *msgLock;
}

-(void) resetHeaderAndData;
@end

@interface FrameAssembler : NSObject {
	BOOL hasFirstFrame;
	BOOL hasSecondFrame;
	NSMutableData *accumulator;
	NSInteger totalSize;
	NSInteger framesRemaining;
	NSArray* listeners;
}
	
-(id) initWithListeners:(NSArray*)listeners;
-(void) handleFirstFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data;
-(void) handleSecondFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data;
-(void) handleRemainingFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data;
-(void) notifyIfFinished:(SDLProtocolFrameHeader*) header;
-(void) handleMultiFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data;
-(void) handleFrame:(SDLProtocolFrameHeader*) header data:(NSData*) data;	
-(SDLMessageType) messageTypeForFrameHeader:(SDLProtocolFrameHeader*)header;
	
@end

@interface BulkAssembler: FrameAssembler {
	NSInteger bulkCorrId;
}

@end