//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc.enums;

public enum PermissionStatus {
	ALLOWED,
	DISALLOWED,
	USER_DISALLOWED,
	USER_CONSENT_PENDING;
	
	public static PermissionStatus valueForString(String value) {
        return valueOf(value);
    }
}
