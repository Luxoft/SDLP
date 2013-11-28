//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLRPCMessage.h"
#import "SDLNames.h"

@implementation SDLRPCStruct

-(id) initWithDictionary:(NSMutableDictionary*) dict {
	if (self = [super init]) {
		store = [dict retain];
	}
	return self;
}

-(id) init {
	if (self = [super init]) {
		store = [[NSMutableDictionary alloc] init];
	}
	return self;
}

-(NSMutableDictionary*) serializeDictionary:(NSDictionary*) dict {
	
	NSMutableDictionary* ret = [NSMutableDictionary dictionaryWithCapacity:dict.count];
	for (NSString* key in [dict keyEnumerator]) {
		NSObject* value = [dict objectForKey:key];
		if ([value isKindOfClass:SDLRPCStruct.class]) {
			[ret setObject:[(SDLRPCStruct*)value serializeAsDictionary] forKey:key];
		} else if ([value isKindOfClass:NSDictionary.class]) {
			[ret setObject:[self serializeDictionary:(NSDictionary*)value] forKey:key];
		} else if ([value isKindOfClass:NSArray.class]) {
			NSArray* arrayVal = (NSArray*) value;
			
			if (arrayVal.count > 0 
				&& ([[arrayVal objectAtIndex:0] isKindOfClass:SDLRPCStruct.class])) {
				NSMutableArray* serializedList = [NSMutableArray arrayWithCapacity:arrayVal.count];
				for (SDLRPCStruct* serializeable in arrayVal) {
					[serializedList addObject:[serializeable serializeAsDictionary]];
				}
				[ret setObject:serializedList forKey:key];
			} else if (arrayVal.count > 0 
					 && ([[arrayVal objectAtIndex:0] isKindOfClass:SDLEnum.class])) {
				NSMutableArray* serializedList = [NSMutableArray arrayWithCapacity:arrayVal.count];
				for (SDLEnum* anEnum in arrayVal) {
					[serializedList addObject:anEnum.value];
				}
				[ret setObject:serializedList forKey:key];
			} else {
				[ret setObject:value forKey:key];
			}
		} else if ([value isKindOfClass:SDLEnum.class]) {
			[ret setObject:((SDLEnum*)value).value forKey:key];
		} else {
			[ret setObject:value forKey:key];
		}
	}
	return ret;
}

-(NSMutableDictionary*) serializeAsDictionary {
	return [self serializeDictionary:store];
}

-(void) dealloc {
    [store release];
    [super dealloc];
}

@end

@implementation SDLRPCMessage

@synthesize messageType;

-(id) initWithName:(NSString*) name {
	if (self = [super init]) {
		function = [[NSMutableDictionary alloc] initWithCapacity:3];
		parameters = [[NSMutableDictionary alloc] init];
		messageType = NAMES_request;
		[store setObject:function forKey:messageType];
		[function setObject:parameters forKey:NAMES_parameters];
		[function setObject:name forKey:NAMES_operation_name];
	}
	return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
	if (self = [super initWithDictionary:dict]) {
		messageType = [[store keyEnumerator] nextObject];
		
		function = [[store objectForKey:messageType] retain];
		parameters = [[function objectForKey:NAMES_parameters] retain];
	}
	return self;
}

-(void) dealloc {
	[function release];
	[parameters release];
	
	[super dealloc];
}

-(NSString*) name {
	return [function objectForKey:NAMES_operation_name];
}

@end
