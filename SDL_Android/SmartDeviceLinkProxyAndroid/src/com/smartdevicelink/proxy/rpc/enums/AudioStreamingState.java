//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum AudioStreamingState {
    AUDIBLE,
    NOT_AUDIBLE;

    public static AudioStreamingState valueForString(String value) {
        return valueOf(value);
    }
}
