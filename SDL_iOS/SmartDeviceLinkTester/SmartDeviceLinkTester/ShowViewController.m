//
// Copyright (c) 2013 Ford Motor Company
//

#import "ShowViewController.h"

@interface ShowViewController ()

@end

@implementation ShowViewController


-(IBAction)sendShowRPC:(id)sender {
    
    SDLTextAlignment *ta;
    if (textalignment.selectedSegmentIndex == 0) {
        ta = [SDLTextAlignment LEFT_ALIGNED];
    }
    else if (textalignment.selectedSegmentIndex == 1) {
        ta = [SDLTextAlignment CENTERED];
    }
    else {
        ta = [SDLTextAlignment RIGHT_ALIGNED];
    }
    
    
    [[SDLBrain getInstance] showAdvancedPressedWithLine1Text:[line1text text] line2:[line2text text] statusBar:[statusbartext text] mediaClock:[mediaclocktext text] mediaTrack:[mediatracktext text] alignment:ta];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"Show";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    line1text.delegate = self;
    line2text.delegate = self;
    statusbartext.delegate = self;
    mediaclocktext.delegate = self;
    mediatracktext.delegate = self;
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
