//
// Copyright (c) 2013 Ford Motor Company
//

#import "AddSubMenuViewController.h"

@interface AddSubMenuViewController ()

@end

@implementation AddSubMenuViewController

-(IBAction)displayPositionSlider:(id)sender {
    positionLabel.text = [NSString stringWithFormat:@"%g",round([positionSlider value])];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}

-(IBAction)addSubMenuPressed:(id)sender {
    
    [subMenuIssued addObject:[[AddMenuOption alloc] initWithMenuName:[menuNameText text] menuId:[NSNumber numberWithInt:[[menuIDText text] intValue]]]];
    
    [[SDLBrain getInstance] addSubMenuPressedwithID:[NSNumber numberWithInt:[[menuIDText text] intValue]] menuName:[menuNameText text] position:[NSNumber numberWithDouble:round([positionSlider value])]];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"AddSubMenu";
    
    subMenuIssued = [[NSMutableArray alloc] init];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    menuNameText.delegate = self;
    menuIDText.delegate = self;
    
    positionSlider.minimumValue = 0;
    positionSlider.maximumValue = 5;
    [positionSlider setValue:1];
    positionLabel.text = @"1";
}

-(void) dealloc {
    [subMenuIssued release];
    [super dealloc];
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
