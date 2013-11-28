//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum InteractionMode {
    MANUAL_ONLY,
    VR_ONLY,
    BOTH;

    public static InteractionMode valueForString(String value) {
        return valueOf(value);
    }
}
