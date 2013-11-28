//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLTextAlignment.h"

@interface ShowViewController : UIViewController <UITextFieldDelegate> {
 
    IBOutlet UITextField *line1text;
    IBOutlet UITextField *line2text;
    IBOutlet UITextField *statusbartext;
    IBOutlet UITextField *mediaclocktext;
    IBOutlet UITextField *mediatracktext;
    
    IBOutlet UISegmentedControl *textalignment;
}

-(IBAction)sendShowRPC:(id)sender;

@end
