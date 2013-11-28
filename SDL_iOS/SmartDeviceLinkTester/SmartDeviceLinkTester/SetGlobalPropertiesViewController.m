//
// Copyright (c) 2013 Ford Motor Company
//

#import "SetGlobalPropertiesViewController.h"

@interface SetGlobalPropertiesViewController ()

@end

@implementation SetGlobalPropertiesViewController


-(IBAction)setGlobalPropertiesPressed:(id)sender {
    [[SDLBrain getInstance] setGlobalPropertiesPressedWithHelpText:[helpText text] timeoutText:[timeoutText text]];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"SetGlobalProperties";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    
    if([text isEqualToString:@"\n"]) {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    helpText.delegate = self;
    timeoutText.delegate = self;
    
    [[helpText layer] setCornerRadius:10];
    [[timeoutText layer] setCornerRadius:10];
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
