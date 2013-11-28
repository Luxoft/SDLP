//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.protocol;

import com.smartdevicelink.protocol.enums.SessionType;
import com.smartdevicelink.transport.ISmartDeviceLinkTransport;
import com.smartdevicelink.transport.ITransportListener;

public interface IProtocol extends ITransportListener {

	void handleBytesFromTransport(byte[] receivedBytes, int receivedBytesLength);
	public void sendStartSession(SessionType sessionType);
	public void sendEndSession(SessionType sessionType, byte sessionID);
	
	public void sendData(SessionType sessionType, byte sessionID, byte[] data);
	
	public ISmartDeviceLinkTransport getTransport();
	public void setTransport(ISmartDeviceLinkTransport transport);
	
	void addProtocolListener(IProtocolListener listener);
	boolean removeProtocolListener(IProtocolListener listener);
	
	public void close();
}
