//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLLanguage : SDLEnum {}

+(SDLLanguage*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLLanguage*) EN_US;
+(SDLLanguage*) ES_MX;
+(SDLLanguage*) FR_CA;

@end
