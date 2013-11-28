//
// Copyright (c) 2013 Ford Motor Company
//

#import "UnregisterAppInterfaceViewController.h"

@interface UnregisterAppInterfaceViewController ()

@end

@implementation UnregisterAppInterfaceViewController

-(IBAction)unregisterAppInterfacePressed:(id)sender {
    [[SDLBrain getInstance] unregisterAppInterfacePressed];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"UnregisterAppInterface";
    
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
