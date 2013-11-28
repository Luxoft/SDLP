//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLConsoleController.h"

@interface ConsoleViewController : UIViewController <SDLDebugToolConsole> {
    UITableView* consoleView;
    SDLConsoleController *consoleController;
    
    
}

@property (nonatomic, retain) IBOutlet UITableView* consoleView;


@end
