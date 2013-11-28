//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"

@interface EncodedSyncPDataViewController : UIViewController <UITextViewDelegate> {
    IBOutlet UITextView *encodedDataText; 
}

-(IBAction)sendESPData:(id)sender;

@end
