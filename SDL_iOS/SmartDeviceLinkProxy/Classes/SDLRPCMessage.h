//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLRPCStruct : NSObject {
	NSMutableDictionary* store;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict;
-(id) init;

-(NSMutableDictionary*) serializeAsDictionary;

@end

@interface SDLRPCMessage : SDLRPCStruct {
	NSMutableDictionary* function;
	NSMutableDictionary* parameters;
	NSString* messageType;
	
}

-(id) initWithName:(NSString*) name;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(readonly) NSString* name;
@property(readonly) NSString* messageType;

@end