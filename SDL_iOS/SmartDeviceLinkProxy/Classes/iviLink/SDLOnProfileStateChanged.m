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

#import "SDLOnProfileStateChanged.h"
#import "IVINames.h"

@implementation SDLOnProfileStateChanged

-(id) init {
    self = [super initWithName: IVI_NAMES_appStateChanged];
    return self;
}

-(id) initWithDictionary:(NSMutableDictionary*) dict {
    self = [super initWithDictionary:dict];
    return self;
}

-(void) setProfileState:(SDLProfileState *)profileState {
    if (profileState != nil) {
        [parameters setObject:profileState forKey:IVI_NAMES_TAG_profileState];
    } else {
        [parameters removeObjectForKey:IVI_NAMES_TAG_profileState];
    }
}

-(SDLProfileState*) profileState {
    NSObject * obj = [parameters objectForKey: IVI_NAMES_TAG_profileState];
    if (obj == nil) {
        return nil;
    }
    if ([obj isKindOfClass:SDLProfileState.class]) {
        return (SDLProfileState*)obj;
    } else {
        return [SDLProfileState valueOf:(NSString*)obj];
    }
}
@end
