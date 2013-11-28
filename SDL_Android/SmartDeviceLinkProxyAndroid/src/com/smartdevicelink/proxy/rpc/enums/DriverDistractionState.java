//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum DriverDistractionState {
	DD_ON,
	DD_OFF;
	
	public static DriverDistractionState valueForString(String value) {
    	return valueOf(value);
    }
}
