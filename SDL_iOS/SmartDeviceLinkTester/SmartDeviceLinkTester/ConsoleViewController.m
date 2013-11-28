//
// Copyright (c) 2013 Ford Motor Company
//

#import "ConsoleViewController.h"
#import "SDLBrain.h"


@interface ConsoleViewController ()
-(void) postConsoleController:(NSNotification *)notif;
-(void) postConsoleControllerMainThread:(NSNotification *)notif;
@end

@implementation ConsoleViewController
@synthesize consoleView;



-(void) logInfo:(NSString*) info {
	[consoleController appendString:info];
}

-(void) logException:(NSException*) ex withMessage:(NSString*) message {
	[consoleController appendString:message];
}

-(void) postConsoleControllerMainThread:(NSNotification *)notif {
    [consoleController appendMessage:[notif object]];

}

-(void) postConsoleController:(NSNotification *)notif{
    [self performSelectorOnMainThread:@selector(postConsoleControllerMainThread:) withObject:notif waitUntilDone:NO];
}



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(postConsoleController:) name:@"NewConsoleControllerObject" object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(postConsoleController:) name:@"onRPCResponse" object:nil];
    
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Console", @"Console");
        self.tabBarItem.image = [UIImage imageNamed:@"cog_02"];
    }

    return self;
}


- (void)viewDidLoad
{
    consoleController = [[SDLConsoleController alloc] initWithTableView:self.consoleView];
    [super viewDidLoad];

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

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [consoleController release];
    [super dealloc];
}

@end
