//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLAbstractTransport.h"

@interface SDLTCPTransport : SDLAbstractTransport {
	CFSocketRef socket;
}

@end
