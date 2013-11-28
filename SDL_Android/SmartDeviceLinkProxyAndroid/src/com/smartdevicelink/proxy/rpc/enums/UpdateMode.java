//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum UpdateMode {
    COUNTUP,
    COUNTDOWN,
    PAUSE,
    RESUME;

    public static UpdateMode valueForString(String value) {
        return valueOf(value);
    }
}
