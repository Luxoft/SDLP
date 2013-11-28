//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "RPC/SDLTTSChunk.h"
#import "SDLJingle.h"

@interface SDLTTSChunkFactory : NSObject {}

+(SDLTTSChunk*) buildTTSChunkForString:(NSString*) text type:(SDLSpeechCapabilities*)type;
+(NSMutableArray*) buildTTSChunksFromSimple:(NSString*) simple;

@end
