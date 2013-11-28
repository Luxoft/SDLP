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

#import "PMMessagesHelper.h"
#import "MF_Base64Additions.h"

@implementation PMMessagesHelper

+ (void)addData:(NSData*)data toDictionary:(NSMutableDictionary*)dict forKey:(NSString*)key {
    if (data != nil) {
        NSString * base64 = [MF_Base64Codec base64StringFromData:data];
        [dict setObject:base64 forKey:key];
        [base64 release];
    } else {
        [dict removeObjectForKey:key];
    }
}

+ (NSData*)getDataFromDictionary:(NSMutableDictionary*)dict forKey:(NSString*)key {
    NSString * str = [dict objectForKey:key];
    if (str == nil)
    {
        return nil;
    }
    return [[MF_Base64Codec dataFromBase64String: str] autorelease];
}

+ (void)addDataAsString:(NSString*)data toDictionary:(NSMutableDictionary*)dict forKey:(NSString*)key {
    if (data != nil) {
        NSData * nsdata = [data dataUsingEncoding:NSUTF8StringEncoding];
        NSString * base64 = [MF_Base64Codec base64StringFromData: nsdata];
        [dict setObject:base64 forKey:key];
        [base64 release];
    } else {
        [dict removeObjectForKey:key];
    }

}
+ (NSString*)getDataAsStringFromDictionary:(NSMutableDictionary*)dict forKey:(NSString*)key {
    NSString * str = [dict objectForKey:key];
    if (str == nil)
    {
        return nil;
    }
    NSData * data = [MF_Base64Codec dataFromBase64String:str];
    NSString * result = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    [data release];
    return result;
}

@end
