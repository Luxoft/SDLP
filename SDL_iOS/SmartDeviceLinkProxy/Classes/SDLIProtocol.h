//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLProtocolListener.h"
#import "SDLProtocolMessage.h"
#import "SDLITransport.h"

@protocol SDLIProtocol<SDLTransportListener>

-(void) handleBytesFromTransport:(Byte*) receivedBytes length:(long) receivedBytesLength;

-(void) sendStartSessionWithType:(SDLSessionType) sessionType;
-(void) sendEndSessionWithType:(SDLSessionType)sessionType sessionID:(Byte)sessionID;
-(void) sendData:(NSData*) data sessionType:(SDLSessionType)sessionType sessionID:(Byte)sessionID;

@property(assign) NSObject<SDLITransport>* transport;

-(void) addProtocolListener:(NSObject<SDLProtocolListener>*) listener;
-(void) removeProtocolListener:(NSObject<SDLProtocolListener>*) listener;

@end