//
// Copyright (c) 2013 Ford Motor Company
//

#import "SetMediaClockTimerViewController.h"

@interface SetMediaClockTimerViewController ()

@end

@implementation SetMediaClockTimerViewController

-(IBAction)setMediaClockTimerPressed:(id)sender {
   
    SDLUpdateMode *ua;
    if (updateControl.selectedSegmentIndex == 0) {
        ua = [SDLUpdateMode COUNTUP];
    }
    else if (updateControl.selectedSegmentIndex == 1) {
        ua = [SDLUpdateMode COUNTDOWN];
    }
    else if (updateControl.selectedSegmentIndex == 2) {
        ua = [SDLUpdateMode PAUSE];
    }
    else {
        ua = [SDLUpdateMode RESUME];
    }
    
    [[SDLBrain getInstance] setMediaClockTimerPressedwithHours:[NSNumber numberWithInt:[[hoursText text] intValue]] minutes:[NSNumber numberWithInt:[[minutesText text] intValue]] seconds:[NSNumber numberWithInt:[[secondsText text] intValue]] updateMode:ua];
    
    hoursText.text = @"";
    minutesText.text = @"";
    secondsText.text = @"";
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"SetMediaClockTimer";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    hoursText.delegate = self;
    minutesText.delegate = self;
    secondsText.delegate = self;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
