//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy;

import android.telephony.TelephonyManager;

public class SmartDeviceLinkProxyConfigurationResources {
	private String _SmartDeviceLinkConfigurationFilePath;
	private TelephonyManager _telephonyManager;
	
	public SmartDeviceLinkProxyConfigurationResources() {
		this(null, null);
	}
	
	public SmartDeviceLinkProxyConfigurationResources(String SmartDeviceLinkConfigurationFilePath, 
			TelephonyManager telephonyManager) {
		_SmartDeviceLinkConfigurationFilePath = SmartDeviceLinkConfigurationFilePath;
		_telephonyManager = telephonyManager;
	}
	
	public void setSmartDeviceLinkConfigurationFilePath(String SmartDeviceLinkConfigurationFilePath) {
		_SmartDeviceLinkConfigurationFilePath = SmartDeviceLinkConfigurationFilePath;
	}
	
	public String getSmartDeviceLinkConfigurationFilePath() {
		return _SmartDeviceLinkConfigurationFilePath;
	}
	
	public void setTelephonyManager(TelephonyManager telephonyManager) {
		_telephonyManager = telephonyManager;
	}
	
	public TelephonyManager getTelephonyManager() {
		return _telephonyManager;
	}
}
