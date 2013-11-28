//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLButtonName.h"

@interface SubscribeButtonViewController : UIViewController <UITableViewDataSource, UITableViewDelegate> {
    
    
    NSMutableArray *buttonList;
    IBOutlet UITableView *buttonTable;
    
}


@end

NSMutableArray *selectedButtons;
