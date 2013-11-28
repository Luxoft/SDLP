//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum MediaClockFormat {
    CLOCK1,
    CLOCK2,
    CLOCKTEXT1,
    CLOCKTEXT2,
    CLOCKTEXT3;

    public static MediaClockFormat valueForString(String value) {
        return valueOf(value);
    }
}
