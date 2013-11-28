//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "UnregisterAppInterfaceViewController.h"
#import "AlertViewController.h"
#import "SpeakViewController.h"
#import "ShowViewController.h"
#import "SetMediaClockTimerViewController.h"
#import "AddCommandViewController.h"
#import "DeleteCommandViewController.h"
#import "AddSubMenuViewController.h"
#import "DeleteSubMenuViewController.h"
#import "CreateInteractionChoiceSetViewController.h"
#import "DeleteInteractionChoiceSetViewController.h"
#import "PerformInteractionViewController.h"
#import "SubscribeButtonViewController.h"
#import "UnsubscribeButtonViewController.h"
#import "EncodedSyncPDataViewController.h"
#import "SetGlobalPropertiesViewController.h"
#import "ResetGlobalPropertiesViewController.h"

// iviLink
#import "LoadProfileViewController.h"
#import "UnloadProfileViewController.h"
#import "RemoveProfileViewController.h"
#import "SendMessageToProfileViewController.h"
#import "ApplicationStateChangedViewController.h"
#import "AddProfileViewController.h"



@interface RPCTestViewController : UITableViewController  {

    NSMutableArray *rpclist;
    
    UnregisterAppInterfaceViewController *unregisterappinterfacevc;
    AlertViewController *alertvc;
    SpeakViewController *speakvc;
    ShowViewController *showvc;
    SetMediaClockTimerViewController *setmediaclocktimervc;
    AddCommandViewController *addcommandvc;
    DeleteCommandViewController *deletecommandvc;
    AddSubMenuViewController *addsubmenuvc;
    DeleteSubMenuViewController *deletesubmenuvc;
    CreateInteractionChoiceSetViewController *createinteractionchoicesetvc;
    DeleteInteractionChoiceSetViewController *deleteinteractionchoicesetvc;
    PerformInteractionViewController *performinteractionvc;
    SubscribeButtonViewController *subscribebuttonvc;
    UnsubscribeButtonViewController *unsubscribebuttonvc;
    EncodedSyncPDataViewController *encodedsyncpdatavc;
    SetGlobalPropertiesViewController *setglobalpropertiesvc;
    ResetGlobalPropertiesViewController *resetglobalpropertiesvc;
    
    LoadProfileViewController *loadProfileViewController;
    UnloadProfileViewController *unloadProfileViewController;
    RemoveProfileViewController *removeProfileViewController;
    SendMessageToProfileViewController *sendMessageToProfileViewController;
    ApplicationStateChangedViewController *appStateChangedViewController;
    AddProfileViewController *addProfileViewController;
}

@end
