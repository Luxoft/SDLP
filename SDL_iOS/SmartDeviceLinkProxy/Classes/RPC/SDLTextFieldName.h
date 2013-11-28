//
// Copyright (c) 2013 Ford Motor Company
//

#import <Foundation/Foundation.h>
#import "SDLEnum.h"

@interface SDLTextFieldName : SDLEnum {}

+(SDLTextFieldName*) valueOf:(NSString*) value;
+(NSMutableArray*) values;

+(SDLTextFieldName*) mainField1;
+(SDLTextFieldName*) mainField2;
+(SDLTextFieldName*) statusBar;
+(SDLTextFieldName*) mediaClock;
+(SDLTextFieldName*) mediaTrack;
+(SDLTextFieldName*) alertText1;
+(SDLTextFieldName*) alertText2;

@end
