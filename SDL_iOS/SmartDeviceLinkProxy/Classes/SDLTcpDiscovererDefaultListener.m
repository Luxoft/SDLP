/*
 *
 * SDLP SDK
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 *
 * Copyright (C) 2013, Luxoft Professional Corp., member of IBS group
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *
 */

/**
 * \brief Default implementation of SDLTcpDiscovererDefaultListener; displays a pop-up with list of found devices.
 * \author Elena Bratanova <ebratanova@luxoft.com>
 * \date 28/06/13
 */

#import "SDLTcpDiscovererDefaultListener.h"
#import "SDLTcpDiscoveredDevice.h"
#import <UIKit/UIKit.h>

@interface SDLTcpDiscovererDefaultListener() {
    id<SDLTcpDiscovererDefaultListenerDelegate> mDelegate;
    NSArray * mListOfDevices;
}

@end

@implementation SDLTcpDiscovererDefaultListener

-(id) initWithCallback:(id<SDLTcpDiscovererDefaultListenerDelegate>)callback {
    self = [super init];
    if (self) {
        mDelegate = callback;
        [mDelegate retain];
    }
    return self;
}

-(void)dealloc {
    [mListOfDevices release];
    mListOfDevices = nil;
    [mDelegate release];
    mDelegate = nil;
    [super dealloc];
}

-(void) onFoundDevices:(NSArray *)listOfDevices
{
    NSLog(@"on some devices found");
    [mListOfDevices release];
    mListOfDevices = listOfDevices;
    [mListOfDevices retain];
    NSString * dismissButtonTitle = nil;
    if ([mDelegate respondsToSelector:@selector(dismissButtonTitle)]) {
        dismissButtonTitle = [mDelegate dismissButtonTitle];
    }
    SBTableAlert * alert = [[SBTableAlert alloc] initWithTitle:@"Discovered devices"
                                             cancelButtonTitle:(dismissButtonTitle == nil? @"Dismiss" : dismissButtonTitle)
                                                 messageFormat: @"Pick one to connect", nil];
    [alert setStyle:SBTableAlertStyleApple];
    [alert setDelegate: self];
    [alert setDataSource: self];
    [alert show];
}

-(void) onFoundNothing {
    NSLog(@"on found nothing");
    [mDelegate onFoundNothing];
}

#pragma mark - SBTableAlertDataSource

-(UITableViewCell*)tableAlert:(SBTableAlert*)tableAlert cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell * cell = [[[SBTableAlertCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil] autorelease];
    [[cell textLabel] setText:[NSString stringWithFormat: @"%@", [[mListOfDevices objectAtIndex: indexPath.row] stringDescription]]];
    [[cell textLabel] setAdjustsFontSizeToFitWidth: YES];
    [[cell textLabel] setAdjustsLetterSpacingToFitWidth: YES];
    return cell;
}

-(NSInteger)tableAlert:(SBTableAlert *)tableAlert numberOfRowsInSection:(NSInteger)section {
    return [mListOfDevices count];
}

-(NSInteger)numberOfSectionsInTableAlert:(SBTableAlert *)tableAlert {
    return 1;
}


#pragma mark - SBTableAlertDelegate
-(void)tableAlert:(SBTableAlert *)tableAlert didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"selected: %i", indexPath.row);
    NSString * port = [[mListOfDevices objectAtIndex:indexPath.row] boundTcpPort];
    NSString * ip = [[mListOfDevices objectAtIndex:indexPath.row] ip];
    [mDelegate onUserSelectedDeviceWithIP:ip tcpPort:port];
}

-(void)tableAlert:(SBTableAlert *)tableAlert didDismissWithButtonIndex:(NSInteger)buttonIndex {
    NSLog(@"did dismiss: %i", buttonIndex);
    if (buttonIndex == 0) {
        [mDelegate onUserCanceledAlert];
    }
}

@end
