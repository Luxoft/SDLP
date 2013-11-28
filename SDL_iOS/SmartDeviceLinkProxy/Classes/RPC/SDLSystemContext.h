//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLSystemContext : SDLEnum {}

+(SDLSystemContext*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLSystemContext*) SYSCTXT_MAIN;
+(SDLSystemContext*) SYSCTXT_VRSESSION;
+(SDLSystemContext*) SYSCTXT_MENU;

@end
