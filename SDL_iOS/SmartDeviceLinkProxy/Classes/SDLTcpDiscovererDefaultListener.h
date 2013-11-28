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

#import <Foundation/Foundation.h>
#import "SDLTcpDiscovererListener.h"
#import "SDLTcpDiscovererDefaultListenerDelegate.h"
#import "SBTableAlert/SBTableAlert.h"

@interface SDLTcpDiscovererDefaultListener : NSObject<SDLTcpDiscovererListener, SBTableAlertDelegate, SBTableAlertDataSource>
-(id) initWithCallback:(id<SDLTcpDiscovererDefaultListenerDelegate>)callback;
@end
