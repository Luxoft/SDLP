//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.transport;

import com.smartdevicelink.exception.SmartDeviceLinkException;

public interface ISmartDeviceLinkTransport {
	
	void connect() throws SmartDeviceLinkException;

	void disconnect();

	boolean sendBytes(byte[] message);
	boolean sendBytes(byte[] message, int offset, int length);

	void addTransportListener(ITransportListener transListener);
	
	String getGuid();	
	String getAppName();	
	void setAppName(String appName);
}
