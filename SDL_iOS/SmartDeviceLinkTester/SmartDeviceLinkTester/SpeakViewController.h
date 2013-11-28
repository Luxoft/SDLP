//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"

@interface SpeakViewController : UIViewController <UITextViewDelegate> {
    
    IBOutlet UITextView *ttstext;
    
}

-(IBAction)sendSpeakRPC:(id)sender;
-(IBAction)sendTTSChunks:(id)sender;

@end
