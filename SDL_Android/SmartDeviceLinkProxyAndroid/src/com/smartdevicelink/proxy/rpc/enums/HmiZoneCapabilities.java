//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum HmiZoneCapabilities {
    FRONT,
    BACK;

    public static HmiZoneCapabilities valueForString(String value) {
        return valueOf(value);
    }
}
