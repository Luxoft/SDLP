//
// Copyright (c) 2013 Ford Motor Company
//

#import "DeleteInteractionChoiceSetViewController.h"

@interface DeleteInteractionChoiceSetViewController ()

@end

@implementation DeleteInteractionChoiceSetViewController


-(IBAction)deleteInteractionPressed:(id)sender {
    [[SDLBrain getInstance] deleteInteractionChoiceSetPressedWithID:[NSNumber numberWithInt:[[idText text] intValue]]];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"DeleteInteractionChoiceSet";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    idText.delegate = self;
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
