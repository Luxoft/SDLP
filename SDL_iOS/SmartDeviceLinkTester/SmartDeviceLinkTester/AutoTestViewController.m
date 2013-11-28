//
// Copyright (c) 2013 Ford Motor Company
//

#import "AutoTestViewController.h"

@interface AutoTestViewController ()

-(void)runUnitTestwithName:(NSString *)xmlTestName attributes:(NSDictionary *)attributeDict;
-(void)masterTestThread;
-(void)onRPCResponse:(NSNotification *)notif;
-(void)showUserPromptWithMessage:(NSString *)msg;
-(void)showResultsofTest;
-(void)resetforNextTest;
-(void)showErrorAlert:(NSString *)errorMessage;
-(NSString *)dataFilePath;
-(void)writeToFile:(NSArray *)dataToWrite;
-(void)sendEmail;
-(void)compareResultwithAttributes:(NSDictionary *)attributeDict;

@end

@implementation AutoTestViewController

-(NSString *)dataFilePath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingFormat:@"/xmltestresults.csv"];
}

-(void)writeToFile:(NSArray *)dataToWrite {
    NSFileHandle *handle;
    handle = [NSFileHandle fileHandleForWritingAtPath:[self dataFilePath]];
    [handle truncateFileAtOffset:[handle seekToEndOfFile]];

    for (int i = 0; i < [dataToWrite count]; i++) {
        [handle writeData:[[dataToWrite objectAtIndex:i] dataUsingEncoding:NSUTF8StringEncoding]];
        [handle writeData:[@"," dataUsingEncoding:NSUTF8StringEncoding]];
    }
    [handle writeData:[@"\n" dataUsingEncoding:NSUTF8StringEncoding]];
}

-(void)sendEmail {
    if ([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
        picker.mailComposeDelegate = self;
        [picker setSubject:@"XML Test Result"];
        [picker addAttachmentData:[NSData dataWithContentsOfFile:[self dataFilePath]] mimeType:@"test/csv" fileName:@"xmltestresults.csv"];
        [picker setMessageBody:@"Attached is the csv output file." isHTML:NO];
        [self presentModalViewController:picker animated:YES];
        [picker release];
    }
    else {
        [self performSelectorOnMainThread:@selector(showErrorAlert:) withObject:@"Error: Cannot Send Mail" waitUntilDone:NO];
    }
}

-(void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error {
    switch (result) {
        case MFMailComposeResultCancelled:
            [self performSelectorOnMainThread:@selector(showErrorAlert:) withObject:@"Mail Cancelled" waitUntilDone:NO];            
            break;
        case MFMailComposeResultFailed:
            [self performSelectorOnMainThread:@selector(showErrorAlert:) withObject:@"Mail Failure" waitUntilDone:NO];
            break;
        default:
            break;
    }
    [self dismissModalViewControllerAnimated:YES];
}


-(void) handleOpenURL:(NSURL *)url {
    NSLog(@"handleOpenURL");
    xmlURLText = [[NSString stringWithFormat:@"%@",url] retain];
    [xmlScriptText setText:xmlURLText];
    NSError *outError;
    xmlData = [[NSData alloc] initWithContentsOfURL:url options: NSDataReadingUncached error:&outError];
}

-(IBAction)beginAutomatedTesting:(id)sender {
    if (testThread) [testThread release];
    testThread = [[NSThread alloc] initWithTarget:self selector:@selector(masterTestThread) object:nil];
    [testThread start];
}

-(void)compareResultwithAttributes:(NSDictionary *)attributeDict {
    [condition lock];
    
    while (!responseReceived) {
        [condition wait];
    }
    
    if ([attributeDict valueForKey:@"correlationID"]) {
        if (![[NSString stringWithFormat:@"%@",[response correlationID]] isEqualToString:[attributeDict valueForKey:@"correlationID"]]) {
            didPassTest = NO;
            thisTestFailed = YES;
        }
    }
    if ([attributeDict valueForKey:@"return"]) {
        if (![[NSString stringWithFormat:@"%@",[response resultCode]] isEqualToString:[attributeDict valueForKey:@"return"]]) {
            didPassTest = NO;
            thisTestFailed = YES;
        }        
    }
    responseReceived = NO;
    response = nil;
    [condition unlock];
}

-(void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
    if ([elementName isEqualToString:@"test"]) {
        
        int numPasses = 0;
        
        for (int numLoops = numIterations; numLoops > 0; numLoops--) {
            thisTestFailed = NO;
            
            if (isUnitTest) {
                [NSThread sleepForTimeInterval:2];
            }
            else {
                [NSThread sleepForTimeInterval:5];
            }

            for (int i = 0; i < [testComponents count]; i=i+2) {
                
                if ([[testComponents objectAtIndex:i] isEqualToString:@"userPrompt"]) {
                    
                    if (!thisTestFailed) {
                        [self performSelectorOnMainThread:@selector(showUserPromptWithMessage:) withObject:[testComponents objectAtIndex:i+1] waitUntilDone:YES];
                    
                        [condition lock];
                        while (!integrationTestisComplete) {
                            [condition wait];
                        }
                    
                        [condition unlock];
                    }
                    integrationTestisComplete = NO;
                }
                else if ([[testComponents objectAtIndex:i] isEqualToString:@"result"]) {
                    [self compareResultwithAttributes:[testComponents objectAtIndex:i+1]];
                }
                else {
                    [self runUnitTestwithName:[testComponents objectAtIndex:i] attributes:[testComponents objectAtIndex:i+1]];
                }
            }
            if (!thisTestFailed) {
                numPasses++;
            }
        }
          
        NSString *resultOfTest;
        if (numPasses == numIterations) {
            resultOfTest = @"Pass";
        }
        else {
            resultOfTest = @"Fail";
        }
        
            NSArray *results = [NSArray arrayWithObjects:testName,resultOfTest,[NSString stringWithFormat:@"%d", numPasses],[NSString stringWithFormat:@"%d",numIterations], nil];
            [self writeToFile:results];
    }
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict {
    
    if ([elementName isEqualToString:@"type"]) {
        NSLog(@"go to type");
        if ([[attributeDict valueForKey:@"type"] isEqualToString:@"unit"]) {
            NSLog(@"Begin Unit Tests");
            isUnitTest = YES;
        }
        else if ([[attributeDict valueForKey:@"type"] isEqualToString:@"integration"]) {
            isUnitTest = NO;
            NSLog(@"integration test");
        }
        else {
            NSLog(@"Error: Neither Unit nor Integration Test");
        }
    }
    else if ([elementName isEqualToString:@"result"]) {
        integrationTestIsNextElement = NO;
        unitTestIsNextElement = NO;
        
        [testComponents addObject:elementName];
        [testComponents addObject:attributeDict];
    }

    else if (unitTestIsNextElement) {
        [testComponents addObject:elementName];
        [testComponents addObject:attributeDict];
       
    }
    else if (integrationTestIsNextElement) {
        integrationTestisComplete = NO;
        [testComponents addObject:elementName];
        [testComponents addObject:attributeDict];
    }
    else if ([elementName isEqualToString:@"test"]) {
        if (isUnitTest) {
             unitTestIsNextElement = YES;
        }
        else {
            integrationTestIsNextElement = YES;
        }
        
        testName = [NSString stringWithFormat:@"%@",[attributeDict valueForKey:@"testName"]];
        [testComponents removeAllObjects];
        
        if ([attributeDict valueForKey:@"iterations"]) {
            numIterations = [[attributeDict valueForKey:@"iterations"] intValue];
        }
        else {
            numIterations = 1;
        }
        
        if (numIterations < 1) {
            numIterations = 1;
        }
        
    }
    else if ([elementName isEqualToString:@"userPrompt"] && !isUnitTest) {   
        
        [testComponents addObject:elementName];
        [testComponents addObject:[attributeDict valueForKey:@"userPrompt"]];
    }
}

-(void)showUserPromptWithMessage:(NSString *)msg {
    UIAlertView *alertPrompt = [[UIAlertView alloc] initWithTitle:@"User Prompt" message:msg delegate:self cancelButtonTitle:@"Yes" otherButtonTitles:@"No",nil];
    [alertPrompt show];
    [alertPrompt release];

}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 1) {
        thisTestFailed = YES;
        didPassTest = NO;
    }
    integrationTestisComplete = YES;
}

-(void)showResultsofTest {
    NSLog(@"show results of test");
    if (didPassTest) {
        [resultOfXMLTest setText:@"Success"];
        [resultOfXMLTest setBackgroundColor:[UIColor greenColor]];
    }
    else {
        [resultOfXMLTest setText:@"Failure"];
        [resultOfXMLTest setBackgroundColor:[UIColor redColor]];
    
    }
    [resultOfXMLTest setHidden:NO];
    [testInProgress setHidden:YES];
}

-(void)resetforNextTest {
    [resultOfXMLTest setHidden:YES];
    [testInProgress setHidden:NO];
}

-(void)masterTestThread {
    @autoreleasepool {    
    if (testXMLParser) {
        [testXMLParser release];
        NSLog(@"release syncTestXMLParser");
    }
        
    if (xmlData != nil) {
        
        if ([[NSFileManager defaultManager] fileExistsAtPath:[self dataFilePath]]) {
            NSError *error;
            if (![[NSFileManager defaultManager] removeItemAtPath:[self dataFilePath] error:&error]) {
                NSLog(@"Error removing files: %@", error);
            }
            NSLog(@"removed file");
        }
        [[NSFileManager defaultManager] createFileAtPath:[self dataFilePath] contents:nil attributes:nil];
        [self writeToFile:[NSArray arrayWithObjects:@"Test Name",@"Result",@"Number of Passes",@"Attempts",nil]];
        NSLog(@"created file");
        
        testXMLParser = [[NSXMLParser alloc] initWithData:xmlData];
        [testXMLParser setDelegate:self];
        NSLog(@"Create syncTestXMLParser");
        unitTestIsNextElement = NO;
        integrationTestIsNextElement = NO;
        isUnitTest = YES;
        didPassTest = YES;
        responseReceived = NO;
        
        [self performSelectorOnMainThread:@selector(resetforNextTest) withObject:nil waitUntilDone:NO]; 
   
        [testXMLParser parse];
        
        [self performSelectorOnMainThread:@selector(showResultsofTest) withObject:nil waitUntilDone:YES];
        [NSThread sleepForTimeInterval:3];
        [self performSelectorOnMainThread:@selector(sendEmail) withObject:nil waitUntilDone:YES];
        
    }
    else {        
        [self performSelectorOnMainThread:@selector(showErrorAlert:) withObject:@"We did not find an XML File. Make sure that you imported the file from your email." waitUntilDone:NO];
    }
    
    NSLog(@"pool release");
    }
}

-(void)showErrorAlert:(NSString *)errorMessage {
    alert = [[UIAlertView alloc] initWithTitle:@"Error" message:errorMessage delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    [alert release];
}



-(void)onRPCResponse:(NSNotification *)notif {
    responseReceived = YES;
    response = (SDLRPCResponse*)[notif object];

}

-(void)runUnitTestwithName:(NSString *)xmlTestName attributes:(NSDictionary *)attributeDict {
    if ([xmlTestName isEqualToString:@"AddCommand"]) {
        SDLAddCommand *req = [SDLRPCRequestFactory buildAddCommandWithID:nil menuName:nil parentID:nil position:nil vrCommands:nil correlationID:nil];
        SDLMenuParams* menuParams = [[[SDLMenuParams alloc] init] autorelease];
        menuParams.menuName = nil;
        menuParams.parentID = nil;
        menuParams.position = nil;
        req.menuParams = menuParams;
        NSMutableArray *vrCommands = [[NSMutableArray alloc] init];
        
        if ([attributeDict valueForKey:@"menuText"]) {
            req.menuParams.menuName = [attributeDict valueForKey:@"menuText"];
        }
        if ([attributeDict valueForKey:@"position"]) {
            req.menuParams.position = [NSNumber numberWithInt:[[attributeDict valueForKey:@"position"] intValue]];
        }
        if ([attributeDict valueForKey:@"parentID"]) {
            req.menuParams.parentID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"parentID"] intValue]];
        }
        if ([attributeDict valueForKey:@"cmdID"]) {
            req.cmdID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"cmdID"] intValue]];
        }
        if ([attributeDict valueForKey:@"vrCommands"]) {
           [vrCommands addObject:[attributeDict valueForKey:@"vrCommands"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        req.vrCommands = vrCommands;
        [[SDLBrain getInstance] sendRPCMessage:req]; 
        [vrCommands release];
    }
    else if ([xmlTestName isEqualToString:@"AddSubMenu"]) {
        SDLAddSubMenu *req = [SDLRPCRequestFactory buildAddSubMenuWithID:nil menuName:nil position:nil correlationID:nil];
        if ([attributeDict valueForKey:@"menuID"]) {
            req.menuID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"menuID"] intValue]];
        }
        if ([attributeDict valueForKey:@"position"]) {
            req.position = [NSNumber numberWithInt:[[attributeDict valueForKey:@"position"] intValue]];
        }
        if ([attributeDict valueForKey:@"menuName"]) {
            req.menuName = [attributeDict valueForKey:@"menuName"];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }        
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"SetMediaClockTimer"]) {
        SDLSetMediaClockTimer *req = [[[SDLSetMediaClockTimer alloc] init] autorelease];
        SDLStartTime *startTime = [[[SDLStartTime alloc] init] autorelease];
        req.startTime = startTime;
        if ([attributeDict valueForKey:@"hours"]) {
            req.startTime.hours = [NSNumber numberWithInt:[[attributeDict valueForKey:@"hours"] intValue]];
        }
        if ([attributeDict valueForKey:@"minutes"]) {
            req.startTime.minutes = [NSNumber numberWithInt:[[attributeDict valueForKey:@"minutes"] intValue]];
        }
        if ([attributeDict valueForKey:@"seconds"]) {
            req.startTime.seconds = [NSNumber numberWithInt:[[attributeDict valueForKey:@"second"] intValue]];
        }
        if ([attributeDict valueForKey:@"updateMode"]) {
            req.updateMode = [SDLUpdateMode valueOf:[attributeDict valueForKey:@"updateMode"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"CreateInteractionChoiceSet"]) {
        SDLCreateInteractionChoiceSet *req = [[[SDLCreateInteractionChoiceSet alloc] init] autorelease];
        SDLChoice *cho = [[SDLChoice alloc] init];
      
        NSMutableArray *choiceSet = [[NSMutableArray alloc] init];
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        if ([attributeDict valueForKey:@"choiceSet"]) {
            cho.choiceID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"choiceSet"] intValue]];
        }
        if ([attributeDict valueForKey:@"choiceSetName"]) {
            cho.menuName = [attributeDict valueForKey:@"choiceSetName"];
        }
        if ([attributeDict valueForKey:@"choiceSetVrCommands"]) {
            cho.vrCommands = [NSArray arrayWithObject:[attributeDict valueForKey:@"choiceSetVrCommands"]];
        }
        if ([attributeDict valueForKey:@"interactionChoiceSetID"]) {
            req.interactionChoiceSetID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"interactionChoiceSetID"] intValue]];
        }
        [choiceSet addObject:cho];
        req.choiceSet = choiceSet;
        [[SDLBrain getInstance] sendRPCMessage:req];
        [choiceSet release];
        [cho release];
    }
    else if ([xmlTestName isEqualToString:@"DeleteInteractionChoiceSet"]) {
        SDLDeleteInteractionChoiceSet *req = [[[SDLDeleteInteractionChoiceSet alloc] init] autorelease];
        if ([attributeDict valueForKey:@"interactionChoiceSetID"]) {
            req.interactionChoiceSetID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"interactionChoiceSetID"] intValue]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"PerformInteraction"]) {
        SDLPerformInteraction *req = [[[SDLPerformInteraction alloc] init] autorelease];
        req.interactionMode = [SDLInteractionMode BOTH];
        if ([attributeDict valueForKey:@"initialPrompt"]) {
            req.initialPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:[attributeDict valueForKey:@"initialPrompt"]];
        }
        if ([attributeDict valueForKey:@"initialText"]) {
            req.initialText = [attributeDict valueForKey:@"initialText"];
        }
        if ([attributeDict valueForKey:@"interactionChoiceSetID"]) {
            req.interactionChoiceSetIDList = [NSArray arrayWithObject:[NSNumber numberWithInt:[[attributeDict valueForKey:@"interactionChoiceSetID"] intValue]]];
        }
        if ([attributeDict valueForKey:@"helpPrompt"]) {
            req.helpPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:[attributeDict valueForKey:@"helpPrompt"]];
        }
        if ([attributeDict valueForKey:@"timeoutPrompt"]) {
            req.timeoutPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:[attributeDict valueForKey:@"timeoutPrompt"]];
        }
        if ([attributeDict valueForKey:@"timeout"]) {
            req.timeout = [NSNumber numberWithInt:[[attributeDict valueForKey:@"timeout"] intValue]];
        }
        if ([attributeDict valueForKey:@"interactionMode"]) {
            req.interactionMode = [SDLInteractionMode valueOf:[attributeDict valueForKey:@"interactionMode"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"DeleteCommand"]) {
        SDLDeleteCommand *req = [[[SDLDeleteCommand alloc] init] autorelease];
        if ([attributeDict valueForKey:@"cmdID"]) {
            req.cmdID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"cmdID"] intValue]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"DeleteSubMenu"]) {
        SDLDeleteSubMenu *req = [[[SDLDeleteSubMenu alloc] init] autorelease];
        if ([attributeDict valueForKey:@"menuID"]) {
            req.menuID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"menuID"] intValue]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"EncodedSyncPData"]) {
        SDLEncodedSyncPData *req = [[[SDLEncodedSyncPData alloc] init] autorelease];
        NSMutableArray *syncData = [[NSMutableArray alloc] init];
        if ([attributeDict valueForKey:@"data"]) {
            [syncData addObject:[attributeDict valueForKey:@"data"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        req.data = syncData;
        [[SDLBrain getInstance] sendRPCMessage:req];
        [syncData release];
    }
    else if ([xmlTestName isEqualToString:@"PauseMediaClockTimer"]) {
        SDLSetMediaClockTimer *req = [SDLRPCRequestFactory buildSetMediaClockTimerWithUpdateMode:[SDLUpdateMode PAUSE] correlationID:nil];
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"ResumeMediaClockTimer"]) {
        SDLSetMediaClockTimer *req = [SDLRPCRequestFactory buildSetMediaClockTimerWithUpdateMode:[SDLUpdateMode RESUME] correlationID:nil];
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"ClearMediaClockTimer"]) {
        SDLShow *req = [SDLRPCRequestFactory buildShowWithMainField1:nil mainField2:nil statusBar:nil mediaClock:@"" mediaTrack:nil alignment:nil correlationID:nil];
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"SetGlobalProperties"]) {
        SDLSetGlobalProperties *req = [[[SDLSetGlobalProperties alloc] init] autorelease];
        if ([attributeDict valueForKey:@"helpPrompt"]) {
            req.helpPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:[attributeDict valueForKey:@"helpPrompt"]];
        }
        if ([attributeDict valueForKey:@"timeoutPrompt"]) {
            req.timeoutPrompt = [SDLTTSChunkFactory buildTTSChunksFromSimple:[attributeDict valueForKey:@"timeoutPrompt"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"ResetGlobalProperties"]) {
        SDLResetGlobalProperties *req = [[[SDLResetGlobalProperties alloc] init] autorelease];
        if ([attributeDict valueForKey:@"properties"]) {
            req.properties = [NSArray arrayWithObject:[SDLGlobalProperty valueOf:[attributeDict valueForKey:@"properties"]]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"Show"]) {
        SDLShow *req = [[[SDLShow alloc] init] autorelease];
        if ([attributeDict valueForKey:@"mainField1"]) {
            req.mainField1 = [attributeDict valueForKey:@"mainField1"];
        }
        if ([attributeDict valueForKey:@"mainField2"]) {
            req.mainField2 = [attributeDict valueForKey:@"mainField2"];
        }
        if ([attributeDict valueForKey:@"alignment"]) {
            req.alignment = [SDLTextAlignment valueOf:[attributeDict valueForKey:@"alignment"]];
        }
        if ([attributeDict valueForKey:@"statusBar"]) {
            req.statusBar = [attributeDict valueForKey:@"statusBar"];
        }
        if ([attributeDict valueForKey:@"mediaClock"]) {
            req.mediaClock = [attributeDict valueForKey:@"mediaClock"];
        }
        if ([attributeDict valueForKey:@"mediaTrack"]) {
            req.mediaTrack = [attributeDict valueForKey:@"mediaTrack"];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"Speak"]) {
        SDLSpeak *req = [[[SDLSpeak alloc] init] autorelease];
        SDLTTSChunk* simpleChunk = [[[SDLTTSChunk alloc] init] autorelease];
        simpleChunk.type = SDLSpeechCapabilities.TEXT;
        if ([attributeDict valueForKey:@"ttsChunks"]) {
            simpleChunk.text = [attributeDict valueForKey:@"ttsChunks"];
        }
        if ([attributeDict valueForKey:@"ttsType"]) {
            simpleChunk.type = [SDLSpeechCapabilities valueOf:[attributeDict valueForKey:@"ttsType"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        req.ttsChunks = [NSMutableArray arrayWithObject:simpleChunk];
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"Alert"]) {
        SDLAlert *req = [[[SDLAlert alloc] init] autorelease];
        SDLTTSChunk* simpleChunk = [[[SDLTTSChunk alloc] init] autorelease];
        simpleChunk.type = SDLSpeechCapabilities.TEXT;
        if ([attributeDict valueForKey:@"ttsChunks"]) {
            simpleChunk.text = [attributeDict valueForKey:@"ttsChunks"];
        }
        if ([attributeDict valueForKey:@"ttsType"]) {
            simpleChunk.type = [SDLSpeechCapabilities valueOf:[attributeDict valueForKey:@"ttsType"]];
        }
        if ([attributeDict valueForKey:@"alertText1"]) {
            req.alertText1 = [attributeDict valueForKey:@"alertText1"];
        } if ([attributeDict valueForKey:@"alertText2"]) {
            req.alertText2 = [attributeDict valueForKey:@"alertText2"];
        }
        if ([attributeDict valueForKey:@"duration"]) {
            req.duration = [NSNumber numberWithDouble:[[attributeDict valueForKey:@"duration"] doubleValue]];
        }
        if ([attributeDict valueForKey:@"playTone"]) {
            req.playTone = [NSNumber numberWithInt:[[attributeDict valueForKey:@"playTone"] intValue]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        req.ttsChunks = [NSMutableArray arrayWithObject:simpleChunk];
        [[SDLBrain getInstance] sendRPCMessage:req];
    }

    else if ([xmlTestName isEqualToString:@"SubscribeButton"]) {
        SDLSubscribeButton *req = [[[SDLSubscribeButton alloc] init] autorelease];
        if ([attributeDict valueForKey:@"buttonName"]) {
            req.buttonName = [SDLButtonName valueOf:[attributeDict valueForKey:@"buttonName"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"UnsubscribeButton"]) {
        SDLUnsubscribeButton *req = [[[SDLUnsubscribeButton alloc] init] autorelease];
        if ([attributeDict valueForKey:@"buttonName"]) {
            req.buttonName = [SDLButtonName valueOf:[attributeDict valueForKey:@"buttonName"]];
        }
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else if ([xmlTestName isEqualToString:@"UnregisterAppInterface"]) {
        SDLUnregisterAppInterface *req = [[[SDLUnregisterAppInterface alloc] init] autorelease];
        if ([attributeDict valueForKey:@"correlationID"]) {
            req.correlationID = [NSNumber numberWithInt:[[attributeDict valueForKey:@"correlationID"] intValue]];
        }
        [[SDLBrain getInstance] sendRPCMessage:req];
    }
    else {
        [self performSelectorOnMainThread:@selector(showErrorAlert:) withObject:[NSString stringWithFormat:@"We encountered an unfamiliar RPC test: %@",xmlTestName] waitUntilDone:NO];
    }
    [SDLDebugTool logInfo:@"Sent RPC Request"];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRPCResponse:) name:@"onRPCResponse" object:nil];
        
    xmlURLText = [NSString stringWithFormat:@""];
    
    testComponents = [[NSMutableArray alloc] init];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Automated Test", @"Automated Test");
        self.tabBarItem.image = [UIImage imageNamed:@"database"];
    }
    return self;
}

-(void) dealloc {
    [testXMLParser release];
    [testThread release];
    [alert release];
    [xmlURLText release];
    [testComponents release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"started viewDidLoad");
    
    if ([xmlURLText isEqualToString:@""]) {
        [xmlScriptText setText: @"No script is loaded. You can load a script by opening up an email attachment."];
    }
    else {
        [xmlScriptText setText:xmlURLText];
    }
    [xmlScriptText setEditable:NO];
    [[xmlScriptText layer] setCornerRadius:5];
    [resultOfXMLTest setHidden:YES];
    [testInProgress setHidden:YES];
    NSLog(@"finished viewDidLoad");
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
