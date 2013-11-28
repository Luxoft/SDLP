//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>

@protocol SDLDebugToolConsole

-(void) logInfo:(NSString*) info;
-(void) logException:(NSException*) ex withMessage:(NSString*) message;

@end

@interface SDLDebugTool : NSObject {}

+(void) addConsole:(NSObject<SDLDebugToolConsole>*) aConsole;
+(void) removeConsole:(NSObject<SDLDebugToolConsole>*) aConsole;
+(void) logInfo:(NSString*) sdlt, ... ; // NS_FORMAT_FUNCTION(1,2);
+(void) logException:(NSException*) ex withMessage:(NSString*) sdlt, ... ; // NS_FORMAT_FUNCTION(2,3);

@end
