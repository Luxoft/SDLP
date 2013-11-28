//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLProxy.h"

@interface SDLProxyFactory : NSObject {}

+(SDLProxy*) buildProxyWithListener:(NSObject<SDLProxyListener>*) listener;
+(SDLProxy*) buildProxyWithListener:(NSObject<SDLProxyListener>*) listener
                              tcpIPAddress: (NSString*) ipaddress
                                   tcpPort: (NSString*) port;
@end
