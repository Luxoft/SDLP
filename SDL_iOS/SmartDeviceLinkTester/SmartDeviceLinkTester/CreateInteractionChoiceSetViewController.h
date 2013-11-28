//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLChoice.h"

@interface CreateInteractionChoiceSetViewController : UIViewController <UITextViewDelegate, UITextFieldDelegate> {
    
    IBOutlet UITextView *choiceSetView;
    IBOutlet UITextField *idText;
    
    int choiceID;
    
}

-(IBAction)createInteractionPressed:(id)sender;

@end
