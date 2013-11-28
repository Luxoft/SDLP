//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>

#import "SDLProxy.h"
#import "SDLNames.h"
#import "SDLJsonEncoder.h"
#import "SDLJsonDecoder.h"
#import "SDLLanguage.h"
#import "SDLDebugTool.h"
#import <objc/runtime.h>
#import "SDLSiphonServer.h"

@interface SDLCallback : NSObject {
	NSObject* target;
	SEL selector;
	NSObject* parameter;
}

@property (nonatomic, retain) NSObject* target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, retain) NSObject* parameter;

@end

@implementation SDLCallback
@synthesize target;
@synthesize selector;
@synthesize parameter;

-(void) dealloc {
	[target release];
	[parameter release];
	
	[super dealloc];
}

@end

@interface SDLProxy ()

-(void) notifyProxyClosed;
-(void) handleProtocolMessage:(SDLProtocolMessage*) msgData;
-(void) performCallback:(SDLCallback*) callback;

@end

@implementation SDLProxy

const float handshakeTime = 10.0;
const float notifyProxyClosedDelay = 0.1;

- (void)handshakeTimerFired {
    [self destroyHandshakeTimer];
    [self performSelector:@selector(notifyProxyClosed) withObject:nil afterDelay:notifyProxyClosedDelay];
}

-(id) initWithTransport:(NSObject<SDLITransport>*) theTransport protocol:(NSObject<SDLIProtocol>*) theProtocol delegate:(NSObject<SDLProxyListener>*) theDelegate {
	if (self = [super init]) {        
        [[EAAccessoryManager sharedAccessoryManager] registerForLocalNotifications];
        
        proxyListeners = [[NSMutableArray alloc] initWithObjects:theDelegate, nil];
        protocol = [theProtocol retain];
        transport = [theTransport retain];
        rpcSessionID = 0;
        
        alreadyDestructed = NO;
        
        [transport addTransportListener:protocol];
        [protocol addProtocolListener:self];
        protocol.transport = transport;
            
        [transport connect];

       return self;
    }
    return self;
}

-(void)destroyHandshakeTimer {
    if (handshakeTimer != nil) {
        [handshakeTimer invalidate];
        [handshakeTimer release];
        handshakeTimer = nil;
    }
}

-(void) destructObjects {
    if(!alreadyDestructed) {
        [self destroyHandshakeTimer];
        
        [transport release];
        transport = nil;
        
        [protocol release];
        protocol = nil;
        
        [proxyListeners release];
        proxyListeners = nil;
        
        alreadyDestructed = YES;

    }
}

-(void) dispose {
    [self destructObjects];
}

-(void) dealloc {
    [self destructObjects];
	[super dealloc];
}

-(NSObject<SDLITransport>*)getTransport {
    return transport;
}

-(NSObject<SDLIProtocol>*)getProtocol {
    return protocol;
}

-(void) addDelegate:(NSObject<SDLProxyListener>*) delegate {
	@synchronized(proxyListeners) {
		[proxyListeners addObject:delegate];
	}
}


-(void) sendRPCRequest:(SDLRPCMessage*) msg {
	@try {
        [SDLDebugTool logInfo:@"Proxy: sendRPCRequest: encoding message: %@", msg];
		NSData* msgData = [[SDLJsonEncoder instance] encodeDictionary:[msg serializeAsDictionary]];
		[protocol sendData:msgData sessionType:SDLSessionType_RPC sessionID:rpcSessionID];
	} @catch (NSException * e) {
		[SDLDebugTool logException:e withMessage:@"Proxy: sendRPCRequest: Failed to send RPC request: %@", msg.name];
	} @finally {}
}
	 
- (void) onProtocolMessageReceived:(SDLProtocolMessage*) msgData {
	
	@try {
		[self handleProtocolMessage:msgData];
	} @catch (NSException * e) {
		[SDLDebugTool logException:e withMessage:@"Proxy: onProtocolMessageReceived: Failed to handle protocol message."];
	} @finally {}
}

-(void) handleProtocolMessage:(SDLProtocolMessage*) msgData {
    // It's possible to run into a scenario in which SYNC fails to send a StartSessionACK. This issue will be caught by the timer that's waiting for a RegisterAppInterfaceResponse. If no RAIResponse is received, a call to onProxyClosed will occur.
	if (msgData.messageType == SDLMessageType_StartSessionACK) {
        if (msgData.sessionType == SDLSessionType_RPC) {
            rpcSessionID = msgData.sessionID;
            [SDLDebugTool logInfo:@"Got rpcSessionID = %i", rpcSessionID];
			
			NSArray *localListeners = nil;
			@synchronized (proxyListeners) {
				localListeners = [proxyListeners copy];
			}
			
            for (NSObject<SDLProxyListener> *listener in localListeners) {
                [listener onProxyOpened];
            }
			
			[localListeners release];
        } else if (msgData.sessionType == SDLSessionType_BulkData) {
            bulkSessionID = msgData.sessionID;
            [SDLDebugTool logInfo:@"Proxy: handleProtocolMessage: Got bulkSessionID = %i", bulkSessionID];
        }
	}
	
	if (msgData.data.length > 0) {
		NSDictionary *msg = [[SDLJsonDecoder instance] decode:msgData.data];
		[self handleRpcMessage:msg];
	}

}

-(void) neverCalled {
	[[SDLAddCommandResponse alloc] release];
	[[SDLAddSubMenuResponse alloc] release];
	[[SDLAlertResponse alloc] release];
	[[SDLCreateInteractionChoiceSetResponse alloc] release];
	[[SDLDeleteCommandResponse alloc] release];
	[[SDLDeleteInteractionChoiceSetResponse alloc] release];
	[[SDLDeleteSubMenuResponse alloc] release];
	[[SDLOnHMIStatus alloc] release];
	[[SDLOnButtonEvent alloc] release];
	[[SDLOnButtonPress alloc] release];
	[[SDLEncodedSyncPDataResponse alloc] release];
	[[SDLOnCommand alloc] release];
	[[SDLOnAppInterfaceUnregistered alloc] release];
	[[SDLPerformInteractionResponse alloc] release];
	[[SDLRegisterAppInterfaceResponse alloc] release];
	[[SDLSetGlobalPropertiesResponse alloc] release];
	[[SDLResetGlobalPropertiesResponse alloc] release];
	[[SDLSetMediaClockTimerResponse alloc] release];
	[[SDLShowResponse alloc] release];
	[[SDLSpeakResponse alloc] release];
	[[SDLSubscribeButtonResponse alloc] release];
	[[SDLUnregisterAppInterfaceResponse alloc] release];
	[[SDLUnsubscribeButtonResponse alloc] release];
    [[SDLGenericResponse alloc] release];
    [[SDLOnDriverDistraction alloc] release];
    [[SDLOnEncodedSyncPData alloc] release];
    [[SDLOnTBTClientState alloc] release];
    
    [[SDLLoadProfileResponse alloc] release];
    [[SDLUnloadProfileResponse alloc] release];
    [[SDLAddProfileResponse alloc] release];
    [[SDLRemoveProfileResponse alloc] release];
    [[SDLSendAppToProfileMessageResponse alloc] release];
    [[SDLAppStateChangedResponse alloc] release];
    
    [[SDLOnProfileStateChanged alloc] release];
    [[SDLOnProfileToAppMessage alloc] release];
    [[SDLOnProfileUnloaded alloc] release];
}

-(void) handleRpcMessage:(NSDictionary*) msg {
	
	NSString* messageType = [[msg keyEnumerator] nextObject];
	NSDictionary* function = [msg objectForKey:messageType];
	NSString* functionName = [function objectForKey:NAMES_operation_name];
	if ([functionName isEqualToString:NAMES_OnAppInterfaceUnregistered] 
			|| [functionName isEqualToString:NAMES_UnregisterAppInterface]) {
		[self notifyProxyClosed];
		return;
	}
    
	if ([messageType isEqualToString:NAMES_response]) {
        [SDLDebugTool logInfo:@"Proxy: handleRpcMessage: Receiving: %@", functionName];
		bool notGenericResponseMessage = ![functionName isEqualToString:@"GenericResponse"];
		if(notGenericResponseMessage) functionName = [NSString stringWithFormat:@"%@Response", functionName];
	}
    
    // Turn off the timer, the handshake has succeeded
    if ([functionName isEqualToString:@"RegisterAppInterfaceResponse"]) {
        [self destroyHandshakeTimer];
    }
    
	NSString* functionClassName = [NSString stringWithFormat:@"SDL%@", functionName];
	Class functionClass = objc_getClass([functionClassName cStringUsingEncoding:NSUTF8StringEncoding]);
    
    // functionObject doesn't leak because performSelector returns a pointer to the same instance that class_createInstance() creates
	NSObject* functionObject = (id)class_createInstance(functionClass, 0);
    
    NSObject* rpcCallbackObject = [functionObject performSelector:@selector(initWithDictionary:) withObject:msg];
	NSString* handlerName = [NSString stringWithFormat:@"on%@:", functionName];

	SEL handlerSelector = NSSelectorFromString(handlerName);
	
	NSArray *localListeners = nil;
	@synchronized (proxyListeners) {
		localListeners = [proxyListeners copy];
	}
	
	for (NSObject<SDLProxyListener> *listener in localListeners) {
		if ([listener respondsToSelector:handlerSelector]) {
			SDLCallback* callback = [[SDLCallback alloc] init];
			callback.target = listener;
			callback.selector = handlerSelector;
			callback.parameter = rpcCallbackObject;
			[self performSelectorOnMainThread:@selector(performCallback:) withObject:callback waitUntilDone:NO];
			// [callback release]; Moved to performCallback to avoid thread race condition
		} else {
			[SDLDebugTool logInfo:@"Proxy: handleRpcMessage: Proxy listener doesn't respond to selector: %@", handlerName];
		}
	}
	[localListeners release];
}

-(void) performCallback:(SDLCallback*) callback {
	@try {
        assert(callback.parameter != nil);
		[callback.target performSelector:callback.selector withObject:callback.parameter];
	} @catch (NSException * e) {
		[SDLDebugTool logException:e withMessage:@"Exception thrown during call to %@ with object %@", callback.target, callback.parameter];
	} @finally {
		[callback release];
	}
}

-(void) onProtocolClosed {
	[self notifyProxyClosed];
}

-(void) notifyProxyClosed {
	if (isConnected) {
		isConnected = NO;
		NSArray *localListeners = nil;
		@synchronized (proxyListeners) {
			localListeners = [proxyListeners copy];
		}
		
		for (NSObject<SDLProxyListener> *listener in localListeners) {
			[listener performSelectorOnMainThread:@selector(onProxyClosed) withObject:nil waitUntilDone:NO];
		}
		[localListeners release];
	}
}

-(void) onError:(NSString*) info exception:(NSException*) e {
	
	NSArray *localListeners = nil;
	@synchronized (proxyListeners) {
		localListeners = [proxyListeners copy];
	}
	
	for (NSObject<SDLProxyListener> *listener in localListeners) {
		[listener performSelectorOnMainThread:@selector(onError:) withObject:e waitUntilDone:NO];
	}
	[localListeners release];
}



- (void) onProtocolOpened {
	isConnected = YES;
	[protocol sendStartSessionWithType:SDLSessionType_RPC];
    [self destroyHandshakeTimer];
    handshakeTimer = [NSTimer scheduledTimerWithTimeInterval:handshakeTime target:self selector:@selector(handshakeTimerFired) userInfo:nil repeats:NO];
    [handshakeTimer retain];
}

+(void)enableSiphonDebug {
    [SDLSiphonServer enableSiphonDebug];
}

+(void)disableSiphonDebug {
    [SDLSiphonServer disableSiphonDebug];
}

@end
