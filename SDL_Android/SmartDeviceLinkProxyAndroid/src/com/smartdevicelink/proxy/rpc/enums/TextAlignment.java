//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum TextAlignment {
    LEFT_ALIGNED,
    RIGHT_ALIGNED,
    CENTERED;

    public static TextAlignment valueForString(String value) {
        return valueOf(value);
    }
}
