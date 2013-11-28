//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum ButtonEventMode {
    BUTTONUP,
    BUTTONDOWN;

    public static ButtonEventMode valueForString(String value) {
        return valueOf(value);
    }
}
