//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLJsonDecoder.h"
#import "SDLNames.h"
#import "JSON.h"

@implementation SDLJsonDecoder

static NSObject<SDLIDecoder>* jsonDecoderInstance;

+(NSObject<SDLIDecoder>*) instance {
	if (jsonDecoderInstance == nil) {
		jsonDecoderInstance = [[SDLJsonDecoder alloc] init];
	}
	return jsonDecoderInstance;
}

-(NSDictionary*) decode:(NSData*) msgBytes{
	NSString* jsonString = [[[NSString alloc] initWithData:msgBytes encoding:NSUTF8StringEncoding] autorelease];
	SBJSON* sbjson = [SBJSON new];
	NSError* error;
	NSDictionary* jsonObject = [sbjson objectWithString:jsonString error:&error];
    [sbjson release];
	return jsonObject;
}

@end
