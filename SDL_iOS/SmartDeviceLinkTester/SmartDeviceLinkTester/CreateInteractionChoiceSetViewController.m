//
// Copyright (c) 2013 Ford Motor Company
//

#import "CreateInteractionChoiceSetViewController.h"

@interface CreateInteractionChoiceSetViewController ()

@end

@implementation CreateInteractionChoiceSetViewController

-(IBAction)createInteractionPressed:(id)sender {
    NSString *choicestring = [choiceSetView text];
    NSArray *tempchoices = [choicestring componentsSeparatedByString:@", "];
    
    NSMutableArray *choices = [[NSMutableArray alloc] init];
    for (int i = 0; i < [tempchoices count]; i++) {
        SDLChoice *cho = [[SDLChoice alloc] init];
        cho.menuName = [tempchoices objectAtIndex:i];
        cho.choiceID = [NSNumber numberWithInt: choiceID++];
        cho.vrCommands = [NSArray arrayWithObject:[tempchoices objectAtIndex:i]];
        [choices addObject:cho];
        [cho release];
    }
    

    [[SDLBrain getInstance] createInteractionChoiceSetPressedWithID:[NSNumber numberWithInt:[[idText text] intValue]] choiceSet:choices];
}


- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    
    if([text isEqualToString:@"\n"]) {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"CreateInteractionChoiceSet";
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    choiceSetView.delegate = self;
    idText.delegate = self;
    [[choiceSetView layer] setCornerRadius:10];
    choiceID = 0;
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
