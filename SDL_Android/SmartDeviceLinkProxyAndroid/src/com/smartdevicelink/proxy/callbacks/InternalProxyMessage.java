//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.callbacks;

public class InternalProxyMessage {
	private String _functionName;
	private final Long mCreationTime;
	
	public InternalProxyMessage(String functionName) {
		this._functionName = functionName;
		mCreationTime = Long.valueOf(System.nanoTime());
	}
	
	public String getFunctionName() {
		return _functionName;
	}
	
	public Long getCreationTime() {
		return mCreationTime;
	}
}
