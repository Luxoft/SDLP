//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLITransport.h"
#import "SDLProxyListener.h"
#import "SDLRPCMessage.h"
#import "SDLIProtocol.h"

@protocol SDLIProxy
-(id)   initWithTransport:(NSObject<SDLITransport>*) transport protocol:(NSObject<SDLIProtocol>*) protocol delegate:(NSObject<SDLProxyListener>*) delegate;

-(void) dispose;
-(void) addDelegate:(NSObject<SDLProxyListener>*) delegate;

-(void) sendRPCRequest:(SDLRPCMessage*) msg;
-(void) handleRpcMessage:(NSDictionary*) msg;

@end
