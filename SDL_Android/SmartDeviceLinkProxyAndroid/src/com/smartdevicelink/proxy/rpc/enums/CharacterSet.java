//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum CharacterSet {
    TYPE2SET,
    TYPE5SET,
    CID1SET,
    CID2SET;

    public static CharacterSet valueForString(String value) {
        return valueOf(value);
    }
}
