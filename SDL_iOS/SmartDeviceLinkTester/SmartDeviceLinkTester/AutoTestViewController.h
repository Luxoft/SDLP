//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "SDLRPCRequestFactory.h"
#import "SDLTTSChunkFactory.h"
#import <MessageUI/MFMailComposeViewController.h>

@interface AutoTestViewController : UIViewController <NSXMLParserDelegate, UIAlertViewDelegate,MFMailComposeViewControllerDelegate, UITextViewDelegate> {
    
    IBOutlet UITextView *xmlScriptText;
    IBOutlet UILabel *resultOfXMLTest;
    IBOutlet UILabel *testInProgress;
    
    NSData *xmlData;
    NSXMLParser *testXMLParser;
    NSThread *testThread;
    NSCondition *condition;
    SDLRPCResponse* response;
    
    BOOL isUnitTest;
    BOOL unitTestIsNextElement;
    BOOL integrationTestIsNextElement;
    BOOL responseReceived;
    BOOL didPassTest;
    BOOL thisTestFailed;
    BOOL integrationTestisComplete;
    NSString *testName;
    NSString *xmlURLText;
    
    NSMutableArray *testComponents;
    
    int numIterations;
    
    UIAlertView *alert;
}

-(IBAction)beginAutomatedTesting:(id)sender;
-(void)handleOpenURL:(NSURL *)url;


@end
