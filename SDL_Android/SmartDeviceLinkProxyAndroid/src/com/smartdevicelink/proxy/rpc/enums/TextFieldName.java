//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum TextFieldName {
    mainField1,
    mainField2,
    statusBar,
    mediaClock,
    mediaTrack,
    alertText1,
    alertText2;

    public static TextFieldName valueForString(String value) {
        return valueOf(value);
    }
}
