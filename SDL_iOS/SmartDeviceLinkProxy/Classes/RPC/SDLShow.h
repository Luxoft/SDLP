//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLRPCRequest.h"

#import "SDLTextAlignment.h"

@interface SDLShow : SDLRPCRequest {}

-(id) init;
-(id) initWithDictionary:(NSMutableDictionary*) dict;

@property(assign) NSString* mainField1;
@property(assign) NSString* mainField2;
@property(assign) SDLTextAlignment* alignment;
@property(assign) NSString* statusBar;
@property(assign) NSString* mediaClock;
@property(assign) NSString* mediaTrack;

@end
