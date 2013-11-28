//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum ButtonPressMode {
    LONG,
    SHORT;

    public static ButtonPressMode valueForString(String value) {
        return valueOf(value);
    }
}
