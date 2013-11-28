//
// Copyright (c) 2013 Ford Motor Company
//

#import "ResetGlobalPropertiesViewController.h"

@interface ResetGlobalPropertiesViewController ()

@end

@implementation ResetGlobalPropertiesViewController


-(IBAction)resetGlobalPropertiesPressed:(id)sender {
    UIButton *tempButton = (UIButton *)sender;
    SDLGlobalProperty *globalProperty;
    if ([tempButton.titleLabel.text isEqualToString:@"Reset Help Prompt"]) {
        globalProperty = [SDLGlobalProperty HELPPROMPT];
    }
    else {
        globalProperty = [SDLGlobalProperty TIMEOUTPROMPT];
    }
    
    [[SDLBrain getInstance] resetGlobalPropertiesPressedwithProperties:[NSArray arrayWithObject:globalProperty]];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"ResetGlobalProperties";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
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
