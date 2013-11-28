//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum GlobalProperty{
    HELPPROMPT,
    TIMEOUTPROMPT;

    public static GlobalProperty valueForString(String value) {
        return valueOf(value);
    }
}
