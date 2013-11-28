//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLITransport.h"
#import "SDLIProtocol.h"

@interface SDLAbstractProtocol : NSObject<SDLIProtocol> {
	NSObject<SDLITransport>* transport;
	NSMutableArray* protocolListeners;
}

@end
