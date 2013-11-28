//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "AddCommandViewController.h"
#import "SDLAddCommandResponse.h"
#import "AddMenuOption.h"

@interface DeleteCommandViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
    
    IBOutlet UITableView *commandsTable;
    
}


@end
