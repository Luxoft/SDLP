//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"

@interface DeleteInteractionChoiceSetViewController : UIViewController <UITextFieldDelegate> {
    
    IBOutlet UITextField *idText;
    
}

-(IBAction)deleteInteractionPressed:(id)sender;

@end
