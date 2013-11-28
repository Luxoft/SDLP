/**
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
 * @author Elena Bratanova <ebratanova@luxoft.com>
 */

#include <memory.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <uuid/uuid.h>
#include <fcntl.h>

#include "CTCPAutoconnectAdapter.hpp"
#include "IHandleGenerator.hpp"
#include <Utils/UUID.hpp>

#define TCP_AUTOCONNECT_INITIAL_PORT 23456
#define UDP_BROADCAST_PORT 45678

#define MAX_CONNECTIONS 128

#define BROADCAST_THREAD_SLEEP_TIMEOUT_PORTIONS 1000
#define BROADCAST_THREAD_SLEEP_TIMEOUT_MICROSEC 1000

namespace 
{

void initSockaddrIn(sockaddr_in& addr, unsigned long s_addr)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_BROADCAST_PORT);
    addr.sin_addr.s_addr = htonl(s_addr);
}

}


NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPDevice::STCPDevice(const char* Name, const in_addr_t & Address):
SDevice(Name),
mAddress(Address)
{
}

NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPDevice::~STCPDevice(void)
{
}

bool NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPDevice::isSameAs(const NsSmartDeviceLink::NsTransportManager::CDeviceAdapter::SDevice * OtherDevice) const
{
    bool result = false;

    if (true == SDevice::isSameAs(OtherDevice))
    {
        const STCPDevice * otherTCPDevice = dynamic_cast<const STCPDevice*>(OtherDevice);

        if (0 != otherTCPDevice)
        {
            result = (mAddress == otherTCPDevice->mAddress);
        }
    }

    return result;
}

NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPConnection::STCPConnection(const NsSmartDeviceLink::NsTransportManager::tDeviceHandle DeviceHandle, int ConnectionSocket, const in_port_t Port):
SConnection(DeviceHandle),
mPort(Port)
{
    mConnectionSocket = ConnectionSocket;
}

NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPConnection::~STCPConnection(void)
{
}

bool NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::STCPConnection::isSameAs(const NsSmartDeviceLink::NsTransportManager::CDeviceAdapter::SConnection* OtherConnection) const
{
    bool result = false;

    if (true == SConnection::isSameAs(OtherConnection))
    {
        const STCPConnection * otherTCPConnection = dynamic_cast<const STCPConnection*>(OtherConnection);

        if (0 != otherTCPConnection)
        {
            result = (mPort == otherTCPConnection->mPort);
        }
    }

    return result;
}

NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::CTCPAutoconnectAdapter(NsSmartDeviceLink::NsTransportManager::IDeviceAdapterListener & Listener, NsSmartDeviceLink::NsTransportManager::IHandleGenerator & HandleGenerator):
CDeviceAdapter(Listener, HandleGenerator)
{
}

NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::~CTCPAutoconnectAdapter(void)
{
    waitForThreadsTermination();
}

NsSmartDeviceLink::NsTransportManager::EDeviceType NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::getDeviceType(void) const
{
    return DeviceWiFi;
}

void NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::mainThread(void)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    int socketFd;
    sockaddr_in serverAddress;
    mBoundPortNumber = TCP_AUTOCONNECT_INITIAL_PORT; 
    while (!mShutdownFlag)
    {
        socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFd == -1)
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "Could not create socket!");
            return;
        }

        const int on = 1;
        if (-1 == setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "setsockopt failed!");
        }
        if (-1 == fcntl(socketFd, F_SETFD, FD_CLOEXEC))
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "FD_CLOEXEC failed!");
        }

        bzero(&serverAddress, sizeof(serverAddress));

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(mBoundPortNumber);

        if (0 != bind(socketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)))
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "bind() failed!");
            close(socketFd);
            mBoundPortNumber ++;
        }
        if (0 != listen(socketFd, MAX_CONNECTIONS))
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "listen() failed!");
            close(socketFd);
            mBoundPortNumber ++;
        }
        else 
        {
            LOG4CPLUS_INFO(mLogger, "Bound to " << mBoundPortNumber << " successfully!");
            break;
        }
    }
    if (mShutdownFlag)
    {
        LOG4CPLUS_INFO(mLogger, "Thread has been stopped while binding!");
        return;
    }

    startBroadcastThread();

    while (false == mShutdownFlag)
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);

        int connectionFd = accept(socketFd, (struct sockaddr*)&clientAddress, &clientAddressSize);

        if (connectionFd >= 0)
        {
            bool isConnectionThreadStarted = false;
            if ((AF_INET == clientAddress.sin_family) && (sizeof(clientAddress) == clientAddressSize))
            {
                char deviceName[32];
                strncpy(deviceName, inet_ntoa(clientAddress.sin_addr), sizeof(deviceName) / sizeof(deviceName[0]));
                LOG4CPLUS_INFO(mLogger, "Connected client " << deviceName);
                tDeviceHandle deviceHandle = InvalidDeviceHandle;
                pthread_mutex_lock(&mDevicesMutex);
                for (tDeviceMap::const_iterator deviceIterator = mDevices.begin(); deviceIterator != mDevices.end(); ++deviceIterator)
                {
                    const STCPDevice * device = dynamic_cast<const STCPDevice *>(deviceIterator->second);
                    if (0 != device)
                    {
                        if (clientAddress.sin_addr.s_addr == device->mAddress)
                        {
                            deviceHandle = deviceIterator->first;
                            break;
                        }
                    }
                }
                pthread_mutex_unlock(&mDevicesMutex);

                if (InvalidDeviceHandle == deviceHandle)
                {
                    deviceHandle = mHandleGenerator.generateNewDeviceHandle();
                    STCPDevice * device = new STCPDevice(deviceName, clientAddress.sin_addr.s_addr);
                    pthread_mutex_lock(&mDevicesMutex);
                    if (true == mDevices.insert(std::make_pair(deviceHandle, device)).second)
                    {
                        device->mUniqueDeviceId = std::string("TCP-") + deviceName;
                        LOG4CPLUS_INFO(mLogger, "Added new device " << deviceHandle << ": " << device->mName << " (" << device->mUniqueDeviceId << ")");
                    }
                    else
                    {
                        LOG4CPLUS_ERROR(mLogger, "Device handle " << deviceHandle << " is already present in devices map");
                        deviceHandle = InvalidDeviceHandle;
                        delete device;
                        device = 0;
                    }
                    pthread_mutex_unlock(&mDevicesMutex);

                    if (0 != device)
                    {
                        updateClientDeviceList();
                    }
                }

                if (InvalidDeviceHandle != deviceHandle)
                {
                    isConnectionThreadStarted = startConnection(new STCPConnection(deviceHandle, connectionFd, clientAddress.sin_port));
                }
                else
                {
                    LOG4CPLUS_ERROR(mLogger, "Failed to insert new device into devices map");
                }
            }
            else
            {
                LOG4CPLUS_ERROR(mLogger, "Address of connected client is invalid");
            }

            if (false == isConnectionThreadStarted)
            {
                close(connectionFd);
            }
        }
        else
        {
            LOG4CPLUS_ERROR_WITH_ERRNO(mLogger, "accept() failed");
        }
    } //  connect loop end
    pthread_join(mBroadcastThread, 0);
}

void NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::connectionThread(const NsSmartDeviceLink::NsTransportManager::tConnectionHandle ConnectionHandle)
{
    handleCommunication(ConnectionHandle);

    tDeviceHandle deviceHandle = InvalidDeviceHandle;

    pthread_mutex_lock(&mConnectionsMutex);

    tConnectionMap::iterator connectionIterator = mConnections.find(ConnectionHandle);

    if (mConnections.end() != connectionIterator)
    {
        STCPConnection * connection = dynamic_cast<STCPConnection*>(connectionIterator->second);

        if (0 != connection)
        {
            deviceHandle = connection->mDeviceHandle;

            delete connection;
        }
        else
        {
            LOG4CPLUS_ERROR(mLogger, "Connection " << ConnectionHandle << " is invalid");
        }

        mConnections.erase(connectionIterator);
    }
    else
    {
        LOG4CPLUS_ERROR(mLogger, "Connection " << ConnectionHandle << " was not found in connections map");
    }

    for (connectionIterator = mConnections.begin(); connectionIterator != mConnections.end(); ++connectionIterator)
    {
        SConnection * connection = connectionIterator->second;

        if (0 != connection)
        {
            if (deviceHandle == connection->mDeviceHandle)
            {
                deviceHandle = InvalidDeviceHandle;
                break;
            }
        }
    }

    pthread_mutex_unlock(&mConnectionsMutex);

    if (InvalidDeviceHandle != deviceHandle)
    {
        LOG4CPLUS_INFO(mLogger, "No connections left for device " << deviceHandle << ". Deleting device");

        pthread_mutex_lock(&mDevicesMutex);

        tDeviceMap::iterator deviceIterator = mDevices.find(deviceHandle);

        if (mDevices.end() != deviceIterator)
        {
            delete deviceIterator->second;

            mDevices.erase(deviceIterator);
        }

        pthread_mutex_unlock(&mDevicesMutex);

        updateClientDeviceList();
    }
}


void * NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::broadcastThread(void * Data)
{
    CTCPAutoconnectAdapter * adapter = (CTCPAutoconnectAdapter*)Data;
    if (adapter)
    {
        adapter->broadcastLoop();
    }
    return 0;
}

void NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::broadcastLoop()
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    struct sockaddr_in srcAddress;
    mBroadcastSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memcpy(mMessage.handshake, BRD_MESSAGE_TEXT, sizeof(mMessage.handshake));
    memset(mMessage.name, 0, sizeof(mMessage.name));
    LOG4CPLUS_INFO(mLogger, "Getting hostname" );
    gethostname(mMessage.name, sizeof(mMessage.name));//Name is generated from Hostname
    mMessage.name[sizeof(mMessage.name)-1]='\0';
    LOG4CPLUS_INFO(mLogger, "Getting hostname =" + std::string(mMessage.name) );
    LOG4CPLUS_INFO(mLogger, "Getting UUID" );

    UUIDStore myUUIDStore;
    if (myUUIDStore.findByName(mMessage.name))
    {
        LOG4CPLUS_INFO(mLogger, "Getting stored UUID" );
        strncpy(mMessage.uuid, myUUIDStore.getByName(mMessage.name).c_str(), sizeof(mMessage.uuid));
        mMessage.uuid[sizeof(mMessage.uuid)-1] = '\0';
        LOG4CPLUS_INFO(mLogger, "Getting stored uuid =" + std::string(mMessage.uuid) );
    }
    else
    {
        LOG4CPLUS_INFO(mLogger, "Getting generated UUID" );
        uuid_t myUUID;
        uuid_generate(myUUID);
        uuid_unparse(myUUID, mMessage.uuid);
        LOG4CPLUS_INFO(mLogger, "Getting generated UUID =" + std::string(mMessage.uuid) );
        myUUIDStore.add(mMessage.name, mMessage.uuid);
    }
    
    mMessage.boundTcpPortNumber = mBoundPortNumber;
    
    int optval = 1;
    setsockopt(mBroadcastSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(mBroadcastSock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
    timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    
    srcAddress.sin_port = htons(UDP_BROADCAST_PORT);
    srcAddress.sin_family = AF_INET;
    srcAddress.sin_addr.s_addr = INADDR_ANY;
    memset(srcAddress.sin_zero, '\0', sizeof(srcAddress.sin_zero));
    bind(mBroadcastSock, (struct sockaddr*)&srcAddress, sizeof(srcAddress));

    while (!mShutdownFlag)
    {
        socklen_t srcAddress_size=sizeof(srcAddress);
        char msgBuffer[sizeof(mMessage) + 1];
        ssize_t packetLength=0;
        LOG4CPLUS_INFO(mLogger, "In listen and reply loop" );
        packetLength = recvfrom(mBroadcastSock, msgBuffer, sizeof(msgBuffer), 0,
            (sockaddr*)&srcAddress, &srcAddress_size);
        if (packetLength == (strlen(BRD_MESSAGE_TEXT) + 1) )
        {
            LOG4CPLUS_INFO(mLogger, "In listen and reply loop: packetLength = " << packetLength);
            msgBuffer[packetLength] = '\0';
            LOG4CPLUS_INFO(mLogger, "In listen and reply loop: buffer = " << msgBuffer);
            if (memcmp(msgBuffer, BRD_MESSAGE_TEXT, strlen(BRD_MESSAGE_TEXT)) == 0)
            {
                LOG4CPLUS_INFO(mLogger, "In listen and reply loop: sending reply " );
                sendto(mBroadcastSock, &mMessage, sizeof(mMessage), 0, (struct sockaddr *)&srcAddress,
                    srcAddress_size);
            }
        }
    }
}


void NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::startBroadcastThread(void)
{
    LOG4CPLUS_TRACE_METHOD(mLogger, __PRETTY_FUNCTION__);
    pthread_create(&mBroadcastThread, 0, &NsSmartDeviceLink::NsTransportManager::CTCPAutoconnectAdapter::broadcastThread,(void*)this);
}
