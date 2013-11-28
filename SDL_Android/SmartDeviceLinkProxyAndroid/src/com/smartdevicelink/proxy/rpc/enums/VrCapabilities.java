//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum VrCapabilities {
    Text;

    public static VrCapabilities valueForString(String value) {
        return valueOf(value);
    }
}
