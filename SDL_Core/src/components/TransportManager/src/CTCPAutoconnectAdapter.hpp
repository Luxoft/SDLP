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

#ifndef __TRANSPORTMANAGER_CTCPAutoconnectAdapter_HPP__
#define __TRANSPORTMANAGER_CTCPAutoconnectAdapter_HPP__

#include <netinet/in.h>

#include "CDeviceAdapter.hpp"
#include "CTCPAutoconnectAdapterCommon.hpp"

namespace NsSmartDeviceLink
{
    namespace NsTransportManager
    {
        /**
         * @brief Device adapter for TCP/IP connections.
         *
         * @see @ref components_transportmanager_internal_design_device_adapters_tcp_adapter
         **/
        class CTCPAutoconnectAdapter: public CDeviceAdapter
        {
        public:
            /**
             * @brief Constructor.
             *
             * @param Listener Listener for device adapter notifications.
             * @param HandleGenerator Handle generator implementation.
             **/
            CTCPAutoconnectAdapter(IDeviceAdapterListener & Listener, IHandleGenerator & HandleGenerator);

            /**
             * @brief Destructor.
             **/
            virtual ~CTCPAutoconnectAdapter(void);

            /**
             * @brief Get type of devices handled by this device adapter.
             *
             * @return Device type.
             **/
            virtual EDeviceType getDeviceType(void) const;

        private:
            /**
             * @brief TCP port for listening for incoming connections.
             *
             * @see @ref components_transportmanager_internal_design_device_adapters_tcp_adapter_listen
             **/
            static const uint16_t CTCPAutoconnectAdapterPort = 12345u;

            /**
             * @brief Internal structure describing TCP device.
             **/
            struct STCPDevice: public SDevice
            {
                /**
                 * @brief Constructor.
                 *
                 * @param Name User-friendly device name.
                 * @param Address Device IP address.
                 **/
                STCPDevice(const char * Name, const in_addr_t & Address);

                /**
                 * @brief Destructor.
                 **/
                virtual ~STCPDevice(void);

                /**
                 * @brief Compare devices.
                 *
                 * This method checks whether two STCPDevice structures
                 * refer to the same device.
                 *
                 * @param OtherDevice Device to compare with.
                 *
                 * @return true if devices are equal, false otherwise.
                 **/
                virtual bool isSameAs(const SDevice * OtherDevice) const;

                /**
                 * @brief Device IP address.
                 **/
                in_addr_t mAddress;
            };

            /**
             * @brief TCP connection.
             **/
            struct STCPConnection: public SConnection
            {
                /**
                 * @brief Constructor.
                 *
                 * @param DeviceHandle Device handle.
                 * @param ConnectionSocket Connection socket.
                 * @param Port TCP port.
                 **/
                STCPConnection(const tDeviceHandle DeviceHandle, int ConnectionSocket, const in_port_t Port);

                /**
                 * @brief Destructor.
                 **/
                virtual ~STCPConnection(void);

                /**
                 * @brief Compare connections.
                 *
                 * This method compares whether two STCPConnection structures
                 * refer to the same connection.
                 *
                 * @param OtherConnection Connection to compare with.
                 *
                 * @return true if connections are equal, false otherwise.
                 **/
                virtual bool isSameAs(const SConnection * OtherConnection) const;

                /**
                 * @brief TCP port of remote device.
                 **/
                const in_port_t mPort;
            };

            /**
             * @brief Device adapter main thread.
             *
             * @see @ref components_transportmanager_internal_design_device_adapters_tcp_adapter_listen
             * @see @ref components_transportmanager_internal_design_device_adapters_tcp_adapter_accept
             * @see @ref components_transportmanager_internal_design_device_adapters_common_main_thread
             **/
            virtual void mainThread(void);

            /**
             * @brief Connection thread.
             *
             * This method is responsible for establishing connection and communicating
             * with remote device via specified connection. It must remove itself from
             * connection map when connection is terminated before terminating connection thread.
             *
             * @param ConnectionHandle Connection handle.
             *
             * @see @ref components_transportmanager_internal_design_device_adapters_tcp_adapter_disconnecting
             * @see @ref components_transportmanager_internal_design_device_adapters_common_connection_thread
             **/
            virtual void connectionThread(const tConnectionHandle ConnectionHandle);

        private:
            static void * broadcastThread(void * Data);
            void startBroadcastThread();
            void broadcastLoop();

        private:
            int32_t mBoundPortNumber;
            int mBroadcastSock;
            tBrdMessage mMessage;
            sockaddr_in mBroadcastAddr;
            pthread_t mBroadcastThread;
        };
    }
}

#endif
