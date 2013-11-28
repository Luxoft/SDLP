//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SDLBrain.h"

@interface UserTestViewController : UIViewController <UITextViewDelegate, AVAudioPlayerDelegate> {
    IBOutlet UITextView *blackboardText;
    IBOutlet UILabel *resultRPCRequest;
    IBOutlet UIImageView *playPauseImage;
    NSString *methodDidGetCalled;
    
    BOOL musicIsPlaying;
    
    AVAudioPlayer *audioPlayer;
}


-(IBAction)showButtonPressed :(id)sender;
-(IBAction)speakButtonPressed :(id)sender;
-(IBAction)alertButtonPressed :(id)sender;
-(IBAction)addCommandPressed:(id)sender;
-(IBAction)playPauseMusic:(id)sender;

@end
