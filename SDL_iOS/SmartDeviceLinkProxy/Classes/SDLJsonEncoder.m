//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLJsonEncoder.h"
#import "SDLNames.h"
#import "JSON.h"
#import "SDLDebugTool.h"

@implementation SDLJsonEncoder

static NSObject<SDLIEncoder>* jsonEncoderInstance;

+(NSObject<SDLIEncoder>*) instance {
	if (jsonEncoderInstance == nil) {
		jsonEncoderInstance = [[SDLJsonEncoder alloc] init];
	}
	return jsonEncoderInstance;
}

-(NSData*) encodeDictionary:(NSDictionary*) dict {
	NSData* ret = nil;
	SBJSON* sbjson = [SBJSON new];
	NSError* error;
	NSString* jsonString = [sbjson stringWithObject:dict error:&error];
    [sbjson release];
    
	ret = [jsonString dataUsingEncoding: NSUTF8StringEncoding];
	return ret;
}

@end
