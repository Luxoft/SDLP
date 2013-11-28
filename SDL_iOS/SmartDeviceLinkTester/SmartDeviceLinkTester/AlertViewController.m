//
// Copyright (c) 2013 Ford Motor Company
//

#import "AlertViewController.h"

@interface AlertViewController ()

@end

@implementation AlertViewController

-(IBAction)alertPressed:(id)sender {
    
    NSString *ttsstring = [ttsView text];
    NSArray *temp = [ttsstring componentsSeparatedByString:@", "];
    NSMutableArray *ttschunks = [[NSMutableArray alloc] init];
    for (int i = 0; i < [temp count]; i++) {
        [ttschunks addObject:[SDLTTSChunkFactory buildTTSChunkForString:[temp objectAtIndex:i] type:[SDLSpeechCapabilities TEXT]]];
    }
 
    [[SDLBrain getInstance] alertAdvancedPressedwithTTSChunks:ttschunks alertText1:[line1Text text] alertText2:[line2Text text] playTone:[NSNumber numberWithBool:[toneSwitch isOn]] duration:[NSNumber numberWithDouble:(round([durationSlider value])*1000)]];
    
    [ttschunks release];
}

-(IBAction)displayDurationSlider:(id)sender {
    durationLabel.text = [NSString stringWithFormat:@"%g",round([durationSlider value])];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
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
    self.title = @"Alert";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    ttsView.delegate = self;
    line1Text.delegate = self;
    line2Text.delegate = self;
    
    [[ttsView layer] setCornerRadius:10];
    
    durationSlider.minimumValue = 3;
    durationSlider.maximumValue = 10;
    [durationSlider setValue:5];
    durationLabel.text = @"5";
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
