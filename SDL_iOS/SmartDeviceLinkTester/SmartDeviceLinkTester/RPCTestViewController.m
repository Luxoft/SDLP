//
// Copyright (c) 2013 Ford Motor Company
//

#import "RPCTestViewController.h"


@interface RPCTestViewController ()

@end

@implementation RPCTestViewController


- (id)initWithStyle:(UITableViewStyle)style {
    self = [super initWithStyle:style];
    if (!self) {
        return self;
    }
    self.title = NSLocalizedString(@"RPC Test", @"RPC Test");
    self.tabBarItem.image = [UIImage imageNamed:@"brief_case"];
    self.title = @"RPC Test";
    
    NSArray *tempArray = [NSArray arrayWithObjects:
                          // -------------
                          @"AddProfile",
                          @"RemoveProfile",
                          @"LoadProfile",
                          @"UnloadProfile",
                          @"SendAppToProfileMessage",
                          @"ApplicationStateChanged",
                          // ---------
                          @"UnregisterAppInterface",
                          @"Alert",
                          @"Speak",
                          @"Show",
                          @"SetMediaClockTimer",
                          @"AddCommand",
                          @"DeleteCommand",
                          @"AddSubMenu",
                          @"DeleteSubMenu",
                          @"CreateInteractionChoiceSet",
                          @"DeleteInteractionChoiceSet",
                          @"PerformInteraction",
                          @"SubscribeButton",
                          @"UnsubscribeButton",
                          @"EncodedSyncPData",
                          @"SetGlobalProperties",
                          @"ResetGlobalProperties", nil];
    rpclist = [[NSMutableArray alloc] init];
    [rpclist addObjectsFromArray:tempArray];
    
    unregisterappinterfacevc = [[UnregisterAppInterfaceViewController alloc] initWithNibName:@"UnregisterAppInterfaceViewController" bundle:nil];
    alertvc = [[AlertViewController alloc] initWithNibName:@"AlertViewController" bundle:nil];    
    speakvc = [[SpeakViewController alloc] initWithNibName:@"SpeakViewController" bundle:nil];
    showvc = [[ShowViewController alloc] initWithNibName:@"ShowViewController" bundle:nil];
    setmediaclocktimervc = [[SetMediaClockTimerViewController alloc] initWithNibName:@"SetMediaClockTimerViewController" bundle:nil];
    addcommandvc = [[AddCommandViewController alloc] initWithNibName:@"AddCommandViewController" bundle:nil];
    deletecommandvc = [[DeleteCommandViewController alloc] initWithNibName:@"DeleteCommandViewController" bundle:nil];
    addsubmenuvc = [[AddSubMenuViewController alloc] initWithNibName:@"AddSubMenuViewController" bundle:nil];
    deletesubmenuvc = [[DeleteSubMenuViewController alloc] initWithNibName:@"DeleteSubMenuViewController" bundle:nil];
    createinteractionchoicesetvc = [[CreateInteractionChoiceSetViewController alloc] initWithNibName:@"CreateInteractionChoiceSetViewController" bundle:nil];
    deleteinteractionchoicesetvc = [[DeleteInteractionChoiceSetViewController alloc] initWithNibName:@"DeleteInteractionChoiceSetViewController" bundle:nil];
    performinteractionvc = [[PerformInteractionViewController alloc] initWithNibName:@"PerformInteractionViewController" bundle:nil];
    subscribebuttonvc = [[SubscribeButtonViewController alloc] initWithNibName:@"SubscribeButtonViewController" bundle:nil];
    unsubscribebuttonvc = [[UnsubscribeButtonViewController alloc] initWithNibName:@"UnsubscribeButtonViewController" bundle:nil];
    encodedsyncpdatavc = [[EncodedSyncPDataViewController alloc] initWithNibName:@"EncodedSyncPDataViewController" bundle:nil];
    setglobalpropertiesvc = [[SetGlobalPropertiesViewController alloc] initWithNibName:@"SetGlobalPropertiesViewController" bundle:nil];
    resetglobalpropertiesvc = [[ResetGlobalPropertiesViewController alloc] initWithNibName:@"ResetGlobalPropertiesViewController" bundle:nil];

    
    loadProfileViewController = [[LoadProfileViewController alloc] initWithNibName: @"LoadProfileViewController" bundle:nil];
    unloadProfileViewController = [[UnloadProfileViewController alloc] initWithNibName: @"LoadProfileViewController" bundle:nil];
    removeProfileViewController = [[RemoveProfileViewController alloc] initWithNibName:@"LoadProfileViewController" bundle:nil];
    sendMessageToProfileViewController = [[SendMessageToProfileViewController alloc] initWithNibName: @"SendMessageToProfileViewController" bundle:nil];
    appStateChangedViewController = [[ApplicationStateChangedViewController alloc] initWithNibName:@"ApplicationStateChangedViewController" bundle:nil];
    addProfileViewController = [[AddProfileViewController alloc] initWithNibName:@"LoadProfileViewController" bundle:nil];
    
    return self;

}


- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [rpclist count]; 
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) { 
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease]; 
    } 
    
    // Configure the cell. 
    cell.textLabel.text = [rpclist objectAtIndex:indexPath.row]; 
    
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    NSString *selectedrpc =  cell.textLabel.text;
   if ([selectedrpc isEqualToString:@"UnregisterAppInterface"]) {
       [self.navigationController pushViewController:unregisterappinterfacevc animated:YES];
    }
    else if ([selectedrpc isEqualToString:@"Alert"]) {
        [self.navigationController pushViewController:alertvc animated:YES];
    }
    else if ([selectedrpc isEqualToString:@"Speak"]) {
        [self.navigationController pushViewController:speakvc animated:YES];
    }
    else if ([selectedrpc isEqualToString:@"Show"]) {
        [self.navigationController pushViewController:showvc animated:YES];
    }
    else if ([selectedrpc isEqualToString:@"SetMediaClockTimer"]) {
        [self.navigationController pushViewController:setmediaclocktimervc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"AddCommand"]) {
        [self.navigationController pushViewController:addcommandvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"DeleteCommand"]) {
        [self.navigationController pushViewController:deletecommandvc animated:YES];
    }
    else if ([selectedrpc isEqualToString:@"AddSubMenu"]) {
        [self.navigationController pushViewController:addsubmenuvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"DeleteSubMenu"]) {
        [self.navigationController pushViewController:deletesubmenuvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"CreateInteractionChoiceSet"]) {
        [self.navigationController pushViewController:createinteractionchoicesetvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"DeleteInteractionChoiceSet"]) {
        [self.navigationController pushViewController:deleteinteractionchoicesetvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"PerformInteraction"]) {
        [self.navigationController pushViewController:performinteractionvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"SubscribeButton"]) {
        [self.navigationController pushViewController:subscribebuttonvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"EncodedSyncPData"]) {
        [self.navigationController pushViewController:encodedsyncpdatavc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"UnsubscribeButton"]) {
        [self.navigationController pushViewController:unsubscribebuttonvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"SetGlobalProperties"]) {
        [self.navigationController pushViewController:setglobalpropertiesvc animated:YES];

    }
    else if ([selectedrpc isEqualToString:@"ResetGlobalProperties"]) {
        [self.navigationController pushViewController:resetglobalpropertiesvc animated:YES];

    }
    // SDLP
    else if([selectedrpc isEqualToString: @"LoadProfile"]) {
        [[self navigationController] pushViewController: loadProfileViewController animated:YES];
    }
    else if([selectedrpc isEqualToString: @"UnloadProfile"]) {
        [[self navigationController] pushViewController: unloadProfileViewController animated:YES];
    }
    else if([selectedrpc isEqualToString: @"RemoveProfile"]) {
        [[self navigationController] pushViewController: removeProfileViewController animated:YES];
    }
    else if ([selectedrpc isEqualToString: @"SendAppToProfileMessage"]) {
        [[self navigationController] pushViewController: sendMessageToProfileViewController animated:YES];
    }
    else if ([selectedrpc isEqualToString: @"ApplicationStateChanged"]) {
        [[self navigationController] pushViewController: appStateChangedViewController animated:YES];
    }
    else if ([selectedrpc isEqualToString: @"AddProfile"]) {
        [[self navigationController] pushViewController:addProfileViewController animated:YES];
    }
}

- (void)loadView
{
    [super loadView];
}

-(void) dealloc {
    [rpclist release];
    [unregisterappinterfacevc release];
    [alertvc release];
    [speakvc release];
    [showvc release];
    [setmediaclocktimervc release];
    [addcommandvc release];
    [deletecommandvc release]; 
    [addsubmenuvc release];
    [deletesubmenuvc release];
    [createinteractionchoicesetvc release];
    [deleteinteractionchoicesetvc release];
    [performinteractionvc release];
    [subscribebuttonvc release];
    [unsubscribebuttonvc release];
    [encodedsyncpdatavc release]; 
    [setglobalpropertiesvc release];
    [resetglobalpropertiesvc release];
    
    // ------
    [loadProfileViewController release];
    [unloadProfileViewController release];
    [removeProfileViewController release];
    [sendMessageToProfileViewController release];
    [appStateChangedViewController release];
    [addProfileViewController release];
    // ------
 
    [super dealloc];
}





@end
