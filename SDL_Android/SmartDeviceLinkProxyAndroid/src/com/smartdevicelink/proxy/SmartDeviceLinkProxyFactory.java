//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy;

import com.smartdevicelink.exception.SmartDeviceLinkException;

public class SmartDeviceLinkProxyFactory {
	
	public static SmartDeviceLinkProxy buildSmartDeviceLinkProxy(IProxyListener listener) {
		SmartDeviceLinkProxy ret = null;
		try {
			ret = new SmartDeviceLinkProxy(listener);
		} catch (SmartDeviceLinkException e) {
			e.printStackTrace();
		}
		return ret;
	}
}
