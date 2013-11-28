//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLIDecoder.h"

@interface SDLJsonDecoder : NSObject<SDLIDecoder> {}

+(NSObject<SDLIDecoder>*) instance;

@end
