//
// Copyright (c) 2013 Ford Motor Company
//

#import <UIKit/UIKit.h>
#import "SDLBrain.h"
#import "AddMenuOption.h"

@interface AddSubMenuViewController : UIViewController <UITextFieldDelegate> {
    
    IBOutlet UITextField *menuNameText;
    IBOutlet UITextField *menuIDText;
    
    IBOutlet UILabel *positionLabel;
    IBOutlet UISlider *positionSlider;
}

-(IBAction)displayPositionSlider:(id)sender;
-(IBAction)addSubMenuPressed:(id)sender;

@end

NSMutableArray *subMenuIssued;