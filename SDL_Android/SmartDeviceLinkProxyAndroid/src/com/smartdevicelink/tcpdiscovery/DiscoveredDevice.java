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
 * @ingroup SDLP TCP Device discovery
 * @author Elena Bratanova <ebratanova@luxoft.com>
 * @date 30.06.2013
 */
package com.smartdevicelink.tcpdiscovery;

public class DiscoveredDevice {
    private String mPort;
    private String mIP;
    private String mName;
    private String mUUID;

    private String mString;

    public String getPort() {
        return mPort;
    }

    public String getIP() {
        return mIP;
    }

    public String getName() {
        return mName;
    }

    public String getUUID() {
        return mUUID;
    }

    public DiscoveredDevice(String ip, int port, String name, String UUID) {
        mIP = ip;
        mPort = "" + port;
        mName = name;
        mUUID = UUID;
        if (name != null && name.length() != 0) {
            mString = "[" + name + "]";
        } else {
            mString = "[" + mIP + ":" + mPort + "]";
        }
    }

    public DiscoveredDevice(String ip, String port) {
        mIP = ip;
        mPort = port;
        mName = "";
        mUUID = "";
        mString = "[" + mIP + ":" + mPort + "]";
    }

    public DiscoveredDevice(String ip, int port) {
        this(ip, "" + port);
    }

    @Override
    public String toString() {
        return mString;
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof DiscoveredDevice)) {
            return false;
        }
        DiscoveredDevice otherInstance = (DiscoveredDevice) o;
        return otherInstance.getIP().equals(mIP) && otherInstance.getPort().equals(mPort);
    }
}
