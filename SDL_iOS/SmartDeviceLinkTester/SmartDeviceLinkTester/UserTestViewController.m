//
// Copyright (c) 2013 Ford Motor Company
//

#import "UserTestViewController.h"

@interface UserTestViewController ()

-(void)showRPCResponse:(NSNotification *)notification;
-(void)hideRPCRequestLabel;

@end

@implementation UserTestViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(showRPCResponse:) name:@"onRPCResponse" object:nil];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"User Test", @"User Test");
        self.tabBarItem.image = [UIImage imageNamed:@"game_controller"];
    }
    return self;
}

-(IBAction)showButtonPressed :(id)sender {
    methodDidGetCalled = @"show";
    [blackboardText setEditable:YES];
    [blackboardText setHidden:NO];   
    [blackboardText becomeFirstResponder];
}

-(IBAction)speakButtonPressed :(id)sender{
    methodDidGetCalled = @"speak";
    [blackboardText setEditable:YES];
    [blackboardText setHidden:NO];      
    [blackboardText becomeFirstResponder];
}

-(IBAction)alertButtonPressed :(id)sender{
    methodDidGetCalled = @"alert";
    [blackboardText setEditable:YES];
    [blackboardText setHidden:NO];      
    [blackboardText becomeFirstResponder];
}

-(IBAction)addCommandPressed:(id)sender {
    methodDidGetCalled = @"addCommand";
    [blackboardText setEditable:YES];
    [blackboardText setHidden:NO];      
    [blackboardText becomeFirstResponder];
}

-(IBAction)playPauseMusic:(id)sender {
    if (musicIsPlaying) {
        //pause music
        musicIsPlaying = NO;
        [playPauseImage setImage:[UIImage imageNamed:@"play.png"]];
        [audioPlayer pause];
        NSLog(@"audioPlayer pause");
    }
    else {
        //play music
        musicIsPlaying = YES;
        [playPauseImage setImage:[UIImage imageNamed:@"pause.png"]];
        [audioPlayer play];
        NSLog(@"audioPlayer play");

    }
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if([text isEqualToString:@"\n"]) {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}

- (void) textViewDidEndEditing:(UITextView *)textView {
    
    NSString *msg = blackboardText.text;
    if ([methodDidGetCalled isEqualToString: @"speak"]) {
        [[SDLBrain getInstance] speakPressed:msg];
    }
    else if ([methodDidGetCalled isEqualToString: @"show"]) {
        [[SDLBrain getInstance] showPressed:msg];

    }
    else if ([methodDidGetCalled isEqualToString: @"alert"]) {
        [[SDLBrain getInstance] alertPressed:msg];
        
    } 
    else if ([methodDidGetCalled isEqualToString: @"addCommand"]) {
        [[SDLBrain getInstance] addCommand:msg];
    }
    blackboardText.text = @"";
    [blackboardText setHidden:YES];
    [blackboardText setEditable:NO];

}

-(void)showRPCResponse:(NSNotification *)notification {
    
    
    SDLRPCResponse* response = (SDLRPCResponse*) [notification object];

    NSString *result = [NSString stringWithFormat:@"%@", [response resultCode]];
    
    if([result isEqualToString:@"SUCCESS"]) {
        [resultRPCRequest setText:@"Success"];
        [resultRPCRequest setBackgroundColor:[UIColor greenColor]];
    }
    else {
        [resultRPCRequest setText:@"Failure"];
        [resultRPCRequest setBackgroundColor:[UIColor redColor]];

    }
    [resultRPCRequest setHidden:NO];
    [self performSelector:@selector(hideRPCRequestLabel) withObject:nil afterDelay:3.0];
}

-(void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    musicIsPlaying = NO;
    [playPauseImage setImage:[UIImage imageNamed:@"play.png"]];
}

-(void)hideRPCRequestLabel {
    [resultRPCRequest setHidden:YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    blackboardText.delegate = self;
    blackboardText.textColor = [UIColor whiteColor];
    [blackboardText setHidden:YES];    
    [blackboardText setEditable:NO];
    [blackboardText setFont:[UIFont fontWithName:@"Arial" size:20]];
    [playPauseImage setImage:[UIImage imageNamed:@"play.png"]];
    [resultRPCRequest setHidden:YES];
    musicIsPlaying = NO;
    
    NSError *error;
    NSURL *path = [[NSBundle mainBundle] URLForResource:@"Sail" withExtension:@"mp3"];
    audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:path error:&error];
    audioPlayer.delegate = self;
    audioPlayer.volume = 0.5;
    //[audioPlayer prepareToPlay];
}

- (void)viewDidUnload
{
    [[SDLBrain getInstance] onProxyClosed];

    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void) dealloc {
    [audioPlayer release];
    [super dealloc];
}

@end
