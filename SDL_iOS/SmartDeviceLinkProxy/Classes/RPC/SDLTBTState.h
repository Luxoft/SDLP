//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"   

@interface SDLTBTState : SDLEnum{}

+(SDLTBTState*) valueOf:(NSString*) value;

+(NSMutableArray*) values;                                 

+(SDLTBTState*) ROUTE_UPDATE_REQUEST; 
+(SDLTBTState*) ROUTE_ACCEPTED;
+(SDLTBTState*) ROUTE_REFUSED; 
+(SDLTBTState*) ROUTE_CANCELLED;

@end


