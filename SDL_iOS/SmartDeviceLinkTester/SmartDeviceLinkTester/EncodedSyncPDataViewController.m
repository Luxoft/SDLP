//
// Copyright (c) 2013 Ford Motor Company
//

#import "EncodedSyncPDataViewController.h"

@interface EncodedSyncPDataViewController ()

@end

@implementation EncodedSyncPDataViewController


-(IBAction)sendESPData:(id)sender {
    [[SDLBrain getInstance] sendEncodedSyncPData:[NSMutableArray arrayWithObjects:[encodedDataText text], nil]];
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
    self.title = @"EncodedSyncPData";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    encodedDataText.delegate = self;
    [[encodedDataText layer] setCornerRadius:10];
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
