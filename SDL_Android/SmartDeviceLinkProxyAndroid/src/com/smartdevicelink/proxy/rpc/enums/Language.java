//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

import java.util.EnumSet;

public enum Language {
    EN_US("EN-US"),
    ES_MX("ES-MX"),
    FR_CA("FR-CA");

    String internalName;
    
    private Language(String internalName) {
        this.internalName = internalName;
    }
    
    public String toString() {
        return this.internalName;
    }
    
    public static Language valueForString(String value) {       	
    	for (Language anEnum : EnumSet.allOf(Language.class)) {
            if (anEnum.toString().equals(value)) {
                return anEnum;
            }
        }
        return null;
    }
}
