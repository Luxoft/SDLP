//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLVRCapabilities : SDLEnum {}

+(SDLVRCapabilities*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLVRCapabilities*) Text;

@end
