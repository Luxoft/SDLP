//
// Copyright (c) 2013 Ford Motor Company
//

#import "AddCommandViewController.h"

@interface AddCommandViewController ()

@end

@implementation AddCommandViewController


-(IBAction)addCommandPressed:(id)sender {
  
    NSArray *voiceCommand = nil;
    NSString *menuName = nil;
    NSString *menuNameTable = nil;
    if ([[menuNameText text] isEqualToString:@""]) {
        [SDLDebugTool logInfo:@"menuNameText is empty"];
        menuNameTable = [[NSString stringWithFormat:@"[%@]", [addVRText text]] retain];
     
    }
    else {
        [SDLDebugTool logInfo:@"menuNameText contains text"];
        menuName = [menuNameText text];
        menuNameTable = menuName;
    }
    
    if (![[addVRText text] isEqualToString:@""]) {
        voiceCommand = [NSArray arrayWithObject:[addVRText text]];
    }
    
    NSNumber *parentID = nil;
    if (![[parentIDText text] isEqualToString:@""]) {
        parentID = [NSNumber numberWithInt:[[parentIDText text] intValue]];
    }
    
    NSNumber *position = nil;
    if (![[positionText text] isEqualToString:@""]) {
        position = [NSNumber numberWithInt:[[positionText text] intValue]];
    }
    
    [SDLDebugTool logInfo:@"cmdID = %d", [[SDLBrain getInstance] getCMDID]];
    
    [commandsIssued addObject:[[[AddMenuOption alloc] initWithMenuName:menuNameTable menuId:[NSNumber numberWithInt:[[SDLBrain getInstance] getCMDID]]] autorelease]];
    
    [SDLDebugTool logInfo:@"Added %@ to commandsIssued",[[commandsIssued lastObject] menuName]];
    
    [SDLDebugTool logInfo:@"Is index number %d",[commandsIssued indexOfObject:[commandsIssued lastObject]]];
    
    [[SDLBrain getInstance] addAdvancedCommandPressedwithMenuName:menuName position:position parentID:parentID vrCommands:voiceCommand];
    
    [SDLDebugTool logInfo:@"sent to Sync"];
    
    [menuNameText setText:@""];
    [addVRText setText:@""];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self.title = @"AddCommand";
    
    commandsIssued = [[NSMutableArray alloc] init];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    menuNameText.delegate = self;
    addVRText.delegate = self;
    parentIDText.delegate = self;
    positionText.delegate = self;
}

-(void) dealloc {
    [commandsIssued release];
    [super dealloc];
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
