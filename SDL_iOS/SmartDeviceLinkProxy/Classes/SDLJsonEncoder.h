//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLIEncoder.h"

@interface SDLJsonEncoder : NSObject<SDLIEncoder> {}

+(NSObject<SDLIEncoder>*) instance;

@end
