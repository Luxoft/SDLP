//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLTBTState.h"

SDLTBTState* SDLTBTState_ROUTE_UPDATE_REQUEST = nil;
SDLTBTState* SDLTBTState_ROUTE_ACCEPTED = nil;
SDLTBTState* SDLTBTState_ROUTE_REFUSED = nil;
SDLTBTState* SDLTBTState_ROUTE_CANCELLED = nil;
NSMutableArray* SDLTBTState_values = nil; 

@implementation SDLTBTState

+(SDLTBTState*) valueOf:(NSString*) value {                       
	for (SDLTBTState* item in SDLTBTState.values) {    
		if ([item.value isEqualToString:value]) { 
			return item; 
		} 
	} 
	return nil; 
}

+(NSMutableArray *) values {           
	if (SDLTBTState_values == nil) {
		SDLTBTState_values = [[NSMutableArray alloc] initWithObjects: 
									SDLTBTState.ROUTE_UPDATE_REQUEST,
									SDLTBTState.ROUTE_ACCEPTED,
									SDLTBTState.ROUTE_REFUSED,
									SDLTBTState.ROUTE_CANCELLED, 
									nil];                        
	} 
	return SDLTBTState_values;
}

+(SDLTBTState*) ROUTE_UPDATE_REQUEST {                                                                        	
	if (SDLTBTState_ROUTE_UPDATE_REQUEST == nil) {
		SDLTBTState_ROUTE_UPDATE_REQUEST = [[SDLTBTState alloc] initWithValue:@"ROUTE_UPDATE_REQUEST"];
	} 
	return SDLTBTState_ROUTE_UPDATE_REQUEST;
}

+(SDLTBTState*) ROUTE_ACCEPTED {                                                                        	
	if (SDLTBTState_ROUTE_ACCEPTED == nil) {
		SDLTBTState_ROUTE_ACCEPTED = [[SDLTBTState alloc] initWithValue:@"ROUTE_ACCEPTED"];
	} 
	return SDLTBTState_ROUTE_ACCEPTED;
}

+(SDLTBTState*) ROUTE_REFUSED {                                                                        	
	if (SDLTBTState_ROUTE_REFUSED == nil) {
		SDLTBTState_ROUTE_REFUSED = [[SDLTBTState alloc] initWithValue:@"ROUTE_REFUSED"];
	} 
	return SDLTBTState_ROUTE_REFUSED;
}

+(SDLTBTState*) ROUTE_CANCELLED {
	if (SDLTBTState_ROUTE_CANCELLED  == nil) {
		SDLTBTState_ROUTE_CANCELLED  = [[SDLTBTState alloc] initWithValue:@"ROUTE_CANCELLED "];
	} 
	return SDLTBTState_ROUTE_CANCELLED;  
}

@end


