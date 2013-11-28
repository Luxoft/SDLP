//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLProtocolMessage.h"

@protocol SDLProtocolListener

-(void) onProtocolMessageReceived:(SDLProtocolMessage*) msg;

-(void) onProtocolOpened;
-(void) onProtocolClosed;
-(void) onError:(NSString*) info exception:(NSException*) e;

@end

