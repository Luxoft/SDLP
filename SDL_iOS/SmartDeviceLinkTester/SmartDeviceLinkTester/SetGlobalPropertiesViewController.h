//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"

@interface SetGlobalPropertiesViewController : UIViewController <UITextViewDelegate> {
    
    IBOutlet UITextView *helpText;
    IBOutlet UITextView *timeoutText;
    
}

-(IBAction)setGlobalPropertiesPressed:(id)sender;

@end
