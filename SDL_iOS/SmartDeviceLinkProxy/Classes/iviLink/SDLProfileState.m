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

#import "SDLProfileState.h"

SDLProfileState* SDLProfileState_BACKGROUND = nil;
SDLProfileState* SDLProfileState_FOREGROUND = nil;
SDLProfileState* SDLProfileState_LIMITED = nil;

NSMutableArray* SDLProfileState_values = nil;

@implementation SDLProfileState

+(SDLProfileState*) valueOf:(NSString*) value {
    for (SDLProfileState* item in SDLProfileState.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLProfileState_values == nil) {
        SDLProfileState_values = [[NSMutableArray alloc] initWithObjects:
                                  [SDLProfileState FOREGROUND],
                                  [SDLProfileState BACKGROUND],
                                  [SDLProfileState LIMITED],
                                  nil];
    }
    return SDLProfileState_values;
}

+(SDLProfileState*) BACKGROUND {
    if (SDLProfileState_BACKGROUND == nil) {
        SDLProfileState_BACKGROUND =
            [[SDLProfileState alloc] initWithValue: @"BACKGROUND"];
    }
    return SDLProfileState_BACKGROUND;
}

+(SDLProfileState*) FOREGROUND {
    if (SDLProfileState_FOREGROUND == nil) {
        SDLProfileState_FOREGROUND =
            [[SDLProfileState alloc] initWithValue: @"FOREGROUND"];
    }
    return SDLProfileState_FOREGROUND;
    
}

+(SDLProfileState*) LIMITED {
    if (SDLProfileState_LIMITED == nil) {
        SDLProfileState_LIMITED =
            [[SDLProfileState alloc] initWithValue: @"LIMITED"];
    }
    return SDLProfileState_LIMITED;
}
@end
