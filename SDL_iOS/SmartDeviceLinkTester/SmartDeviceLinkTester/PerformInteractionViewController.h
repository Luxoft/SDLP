//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLInteractionMode.h"
#import "SDLTTSChunkFactory.h"

@interface PerformInteractionViewController : UIViewController <UITextFieldDelegate, UITextViewDelegate> {
    
    IBOutlet UITextView *initPromptText;
    IBOutlet UITextField *initialText;
    IBOutlet UITextField *choiceIDText;
    IBOutlet UITextView *helpText;
    IBOutlet UITextView *timeoutText;
    
    IBOutlet UISegmentedControl *interactionModeControl;
    
    IBOutlet UILabel *timeoutLabel;
    IBOutlet UISlider *timeoutSlider;
    
    IBOutlet UIScrollView *scrollView;
    
}

-(IBAction)displayTimeoutSlider:(id)sender;
-(IBAction)performInteractionPressed:(id)sender;

@end
