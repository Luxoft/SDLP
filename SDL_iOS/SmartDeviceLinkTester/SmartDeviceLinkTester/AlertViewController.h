//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLTTSChunkFactory.h"

@interface AlertViewController : UIViewController <UITextFieldDelegate, UITextViewDelegate> {
    
    IBOutlet UITextView *ttsView;
    IBOutlet UITextField *line1Text;
    IBOutlet UITextField *line2Text;
    IBOutlet UISwitch *toneSwitch;
    
    IBOutlet UILabel *durationLabel;
    IBOutlet UISlider *durationSlider;
    
}

-(IBAction)alertPressed:(id)sender;
-(IBAction)displayDurationSlider:(id)sender;


@end
