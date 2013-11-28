//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "AddMenuOption.h"

@interface AddCommandViewController : UIViewController <UITextFieldDelegate> {
    
    IBOutlet UITextField *menuNameText;
    IBOutlet UITextField *addVRText;
    IBOutlet UITextField *parentIDText;
    IBOutlet UITextField *positionText;
    
   
    
}

-(IBAction)addCommandPressed:(id)sender;

@end

NSMutableArray *commandsIssued;