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
 * \brief Performs discovery of devices to connect via TCP/IP
 * \author Elena Bratanova <ebratanova@luxoft.com>
 * \date 28/06/13
 */

#import "SDLTcpDiscoverer.h"
#import "SDLTcpDiscovererDefaultListener.h"
#import "SDLTcpDiscoveredDevice.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>

#define UDP_PORT_NUMBER 45678
#define MAX_SOCK_ADDR 128
#define RECEIVE_BUFFER_SIZE 1024
#define HANDSHAKE_TEXT "SMARTDEVICELINK"

static const int NAME_SIZE = 32;
static const int UUID_SIZE = 36;

#define SEARCH_TIMEOUT_MILLIS 2000

@interface SDLTcpDiscoverer()
{
    int mBroadcastSock;
    SDLTcpDiscovererDefaultListener * mOwnedListener;
    id<SDLTcpDiscovererListener> mListener;
    struct sockaddr_in mBroadcastAddr;
    struct sockaddr_in mInAddr;

}
-(void) setupSocket;
-(void) backdroundSearch;

-(BOOL) isTimeout:(UInt64)beginMillis;

-(UInt64) getCurrentTime;
@end

@implementation SDLTcpDiscoverer

-(id) initWithListener:(id<SDLTcpDiscovererListener>)listener {
    self = [super init];
    if (self) {
        mListener = listener;
    }
    return self;
}

-(id) initWithDefaultListener:(id<SDLTcpDiscovererDefaultListenerDelegate>)callback {
    self = [super init];
    if (self) {
        mOwnedListener = [[SDLTcpDiscovererDefaultListener alloc] initWithCallback:callback];
        mListener = mOwnedListener;
    }
    return self;
}

-(void) dealloc {
    [mOwnedListener release];
    close(mBroadcastSock);
    [super dealloc];
}


-(void) setupSocket {
    mBroadcastSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int optval = 1;
    setsockopt(mBroadcastSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(mBroadcastSock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 500000; // half a second
    setsockopt(mBroadcastSock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    memset(&mInAddr, 0, sizeof(mInAddr));
    memset(&mBroadcastAddr, 0, sizeof(mBroadcastAddr));
    mBroadcastAddr.sin_family = AF_INET;
    mBroadcastAddr.sin_port = htons(UDP_PORT_NUMBER);
    mBroadcastAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    mInAddr.sin_family = AF_INET;
    mInAddr.sin_port = htons(UDP_PORT_NUMBER);
    mInAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(mBroadcastSock, (struct sockaddr*)&mInAddr, sizeof(mInAddr)) == -1)
    {
        NSLog(@"error binding: %s", strerror(errno));
    }
}

-(void) performSearch {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self backdroundSearch];
    });
}

-(void) backdroundSearch {
    static const size_t addressLength = MAX_SOCK_ADDR;
    static const SInt32 packetSize = sizeof(HANDSHAKE_TEXT) + sizeof(UInt32);
    
    [self setupSocket];
    NSMutableArray * foundDevices = [[NSMutableArray alloc] init];
    int32_t remotePort;
    char buffer[RECEIVE_BUFFER_SIZE];
    struct sockaddr_in clientAddr;
    struct sockaddr* const clientAddrCastPointer = (struct sockaddr*)&clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    char remoteAddressBuffer[addressLength];
    const UInt64 beginTime = [self getCurrentTime];
    sendto(mBroadcastSock, HANDSHAKE_TEXT, sizeof(HANDSHAKE_TEXT), 0, (struct sockaddr*)&mBroadcastAddr, sizeof(mBroadcastAddr));
    
    while (![self isTimeout:beginTime]) {
        bzero(buffer, sizeof(buffer));
        ssize_t size = recvfrom(mBroadcastSock, buffer, RECEIVE_BUFFER_SIZE, 0, clientAddrCastPointer, &clientAddrSize);
        if (size == -1) {
            NSLog(@"Error receiving! size: %zi, errno: %i, %s", size, errno, strerror(errno));
            continue;
        } else {
            if (size < packetSize) {
                NSLog(@"incorrect packet size! = %zi, should be %zi", size, packetSize);
                continue;
            }
            struct sockaddr_in const* sin = (struct sockaddr_in const*)(clientAddrCastPointer);
            if (strncmp(buffer, HANDSHAKE_TEXT, sizeof(HANDSHAKE_TEXT)) != 0) {
                NSLog(@"incorrect handshake message: %s", buffer);
                continue;
            }
            memcpy(&remotePort, buffer + sizeof(HANDSHAKE_TEXT), sizeof(remotePort));
            NSLog(@"remote port: %zi", remotePort);
            if (inet_ntop(AF_INET, &sin->sin_addr, remoteAddressBuffer, addressLength) != 0) {
                SDLTcpDiscoveredDevice * newDevice = [[SDLTcpDiscoveredDevice alloc] init];
                [newDevice setIp: [NSString stringWithFormat:@"%s", remoteAddressBuffer]];
                [newDevice setBoundTcpPort: [NSString stringWithFormat:@"%zi", remotePort]];
                if (size == sizeof(HANDSHAKE_TEXT) + sizeof(remotePort) + NAME_SIZE + UUID_SIZE)
                {
                    NSLog(@"probably have name!");
                    char  * name = buffer + sizeof(HANDSHAKE_TEXT) + sizeof(remotePort);
                    NSLog(@"name: %s", name);
                    char * uid = buffer + sizeof(HANDSHAKE_TEXT) + sizeof(remotePort) + NAME_SIZE;
                    NSLog(@"uid: %s", name);
                    [newDevice setName: [NSString stringWithFormat:@"%s", name]];
                    [newDevice setUuid:[NSString stringWithFormat:@"%s", uid]];
                }
                BOOL found = NO;
                for (SDLTcpDiscoveredDevice *device in foundDevices) {
                    if ([[device ip] isEqualToString: [newDevice ip]]) {
                        found = YES;
                        break;
                    }
                }
                if (!found) {
                    [foundDevices addObject: newDevice];
                } else {
                    NSLog(@"List of found devices already contains: %@", [newDevice stringDescription]);
                }
                [newDevice release];
            } 
        }
    }
    close(mBroadcastSock);
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([foundDevices count] != 0) {
            [mListener onFoundDevices: foundDevices];
        } else {
            [mListener onFoundNothing];
        }
        [foundDevices release];
    });
}

-(BOOL) isTimeout:(UInt64)beginMillis {
    UInt64 currentTime = [self getCurrentTime];
    return currentTime - beginMillis >= SEARCH_TIMEOUT_MILLIS;
}

-(UInt64) getCurrentTime {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
@end
