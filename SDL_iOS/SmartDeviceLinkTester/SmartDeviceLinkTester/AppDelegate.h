//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVAudioSettings.h>

#import "UserTestViewController.h"
#import "RPCTestViewController.h"
#import "AutoTestViewController.h"
#import "ConsoleViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate, UITabBarControllerDelegate> {
    UserTestViewController *userTestViewController;
    AutoTestViewController *autoTestViewController;
    ConsoleViewController *consoleViewController;
    
    UINavigationController *navController;
}
  
@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) UITabBarController *tabBarController;



@end



