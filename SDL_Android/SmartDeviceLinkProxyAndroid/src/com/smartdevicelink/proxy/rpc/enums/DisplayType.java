//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum DisplayType {
    CID,
    TYPE2,
    TYPE5,
    NGN,
    GEN2_4_DMA,
    GEN2_8_DMA,
    GEN2_4_HUD;

    public static DisplayType valueForString(String value) {
        return valueOf(value);
    }
}
