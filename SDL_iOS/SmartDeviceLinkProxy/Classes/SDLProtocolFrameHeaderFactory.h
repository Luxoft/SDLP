//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLProtocolFrameHeader.h"

@interface SDLProtocolFrameHeaderFactory : NSObject {}

+(SDLProtocolFrameHeader*) parseHeader:(NSData*) header;
+(SDLProtocolFrameHeader*) startSessionWithSessionType:(SDLSessionType)sessionType;
+(SDLProtocolFrameHeader*) endSessionWithSessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID;
+(SDLProtocolFrameHeader*) singleFrameWithSessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID dataSize:(NSInteger)dataSize;
+(SDLProtocolFrameHeader*) firstFrameWithSessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID;
+(SDLProtocolFrameHeader*) consecutiveFrameWithSessionType:(SDLSessionType) sessionType sessionID:(Byte)sessionID dataSize:(NSInteger)dataSize ;

@end
