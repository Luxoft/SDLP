//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLITransport.h"
#import "SDLIProtocol.h"
#import "SDLProxyListener.h"
#import "SDLRPCRequestFactory.h"
#import "SDLIProxy.h"

@interface SDLProxy : NSObject<SDLProtocolListener> {
	NSObject<SDLITransport>* transport;
	NSObject<SDLIProtocol>* protocol;
	NSMutableArray* proxyListeners;
	Byte rpcSessionID;
	Byte bulkSessionID;
	
    NSTimer* handshakeTimer;
    
	BOOL isConnected;
    BOOL alreadyDestructed;
}

-(id)  initWithTransport:(NSObject<SDLITransport>*) transport protocol:(NSObject<SDLIProtocol>*) protocol delegate:(NSObject<SDLProxyListener>*) delegate;

-(void) dispose;
-(void) addDelegate:(NSObject<SDLProxyListener>*) delegate;

-(void) sendRPCRequest:(SDLRPCMessage*) msg;
-(void) handleRpcMessage:(NSDictionary*) msg;
-(NSObject<SDLITransport>*)getTransport;
-(NSObject<SDLIProtocol>*)getProtocol;
-(void)destroyHandshakeTimer;

+(void)enableSiphonDebug;
+(void)disableSiphonDebug;

@end
