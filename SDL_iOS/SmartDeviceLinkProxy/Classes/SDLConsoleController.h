//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLRPCMessage.h"
#import "SDLDebugTool.h"

@interface SDLConsoleController : UITableViewController <SDLDebugToolConsole> {
	NSMutableArray* messageList;
    BOOL atBottom;
}

@property (readonly) NSMutableArray *messageList;

-(id) initWithTableView:(UITableView*) tableView;

-(void) appendString:(NSString*) toAppend;
-(void) appendMessage:(SDLRPCMessage*) toAppend;

@end
