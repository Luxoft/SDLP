//
// Copyright (c) 2013 Ford Motor Company
//

#import "SpeakViewController.h"

@interface SpeakViewController ()

@end

@implementation SpeakViewController

-(IBAction)sendSpeakRPC:(id)sender {
    [[SDLBrain getInstance] speakPressed:[ttstext text]];
}

-(IBAction)sendTTSChunks:(id)sender {
    [[SDLBrain getInstance] speakTTSChunksPressed];
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    
    if([text isEqualToString:@"\n"]) {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"Speak";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    ttstext.delegate = self;
    [[ttstext layer] setCornerRadius:10];

    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
