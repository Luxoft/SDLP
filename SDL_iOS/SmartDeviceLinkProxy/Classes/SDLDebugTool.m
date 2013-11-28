//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLDebugTool.h"
#import "SDLSiphonServer.h"
#import "SDLVersion.h"

#define LOG_INFO_ENABLED
#define LOG_ERROR_ENABLED

static NSMutableArray* debugToolConsoleList = nil;

@implementation SDLDebugTool

+(NSMutableArray*) getConsoleList {
	if (debugToolConsoleList == nil) {
		debugToolConsoleList = [[NSMutableArray alloc] initWithCapacity:2];
	}
	return debugToolConsoleList;
}


+(void) addConsole:(NSObject<SDLDebugToolConsole>*) aConsole {
	[[SDLDebugTool getConsoleList] addObject:aConsole];
}

+(void) removeConsole:(NSObject<SDLDebugToolConsole>*) aConsole {
	[[SDLDebugTool getConsoleList] removeObject:aConsole];
}

+(void) logInfo:(NSString*) sdlt, ... {
	NSString* toOutRaw = nil;
	
    va_list args;
    va_start(args, sdlt);
        
    toOutRaw = [[NSString alloc] initWithFormat:sdlt arguments:args];
    
    NSMutableString *toOut = [[NSMutableString alloc] initWithFormat:@"SDLDebugTool: "];
    
    [toOut appendString:toOutRaw];
    
    [toOutRaw release];
    
	va_end(args);
	
    [SDLSiphonServer init];
    bool dataLogged = [SDLSiphonServer _siphonNSLogData:toOut];
    
    
#ifdef LOG_INFO_ENABLED
    if(!dataLogged){
        NSLog(@"%@", toOut);
    }
#endif
    
	for (NSObject<SDLDebugToolConsole>* console in debugToolConsoleList) {
		[console logInfo:toOut];
	}
    
    [toOut release];
}

+(void) logException:(NSException*) ex withMessage:(NSString*) sdlt, ...  {
	NSString* toOutRaw = nil;
	
	va_list args;
	va_start(args, sdlt);

    toOutRaw = [[NSString alloc] initWithFormat:sdlt arguments:args];
    
    NSMutableString *toOut = [[NSMutableString alloc] initWithFormat:@"%@: ", VERSION_STRING];
    [toOut appendString:toOutRaw];
    
    [toOutRaw release];
    
    va_end(args);
    
    [SDLSiphonServer init];
    bool dataLogged = [SDLSiphonServer _siphonNSLogData:toOut];
    if (dataLogged) {
        dataLogged = [SDLSiphonServer _siphonNSLogData:[ex reason]];
    } // end-if
    
	
#ifdef LOG_ERROR_ENABLED
	if (!dataLogged) {
        NSLog(@"%@: %@", toOut, ex);
    }
#endif
	
	for (NSObject<SDLDebugToolConsole>* console in debugToolConsoleList) {
		[console logException:ex withMessage:toOut];
	}
    
    [toOut release];
}

@end
