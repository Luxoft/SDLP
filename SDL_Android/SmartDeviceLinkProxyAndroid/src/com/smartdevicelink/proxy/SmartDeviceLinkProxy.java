//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy;

import java.util.Vector;

import com.smartdevicelink.exception.SmartDeviceLinkException;
import com.smartdevicelink.exception.SmartDeviceLinkExceptionCause;
import com.smartdevicelink.proxy.rpc.SyncMsgVersion;
import com.smartdevicelink.proxy.rpc.enums.Language;
import com.smartdevicelink.trace.SyncTrace;

public class SmartDeviceLinkProxy extends SmartDeviceLinkProxyBase<IProxyListener> {
	
	private static final String SMARTDEVICELINK_LIB_TRACE_KEY = "42baba60-eb57-11df-98cf-0800200c9a66";
	private static final String SMARTDEVICELINK_LIB_PRIVATE_TOKEN = "{DAE1A88C-6C16-4768-ACA5-6F1247EA01C2}";

	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxy(IProxyListener listener) throws SmartDeviceLinkException {
		super(	listener, 
				/*application context*/null, 
				/*enable advanced lifecycle management*/false, 
				/*app name*/ null,
				/*ngn media screen app name*/null,
				/*vr synonyms*/null,
				/*is media app*/ null,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				/*callbackToUIThread*/ true);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxy instance passing in: IProxyListener.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param applicationContext - Context of the application. Used to access application specific resources.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxy(IProxyListener listener, SmartDeviceLinkProxyConfigurationResources SmartDeviceLinkProxyConfigurationResources) 
		throws SmartDeviceLinkException {
		super(	listener, 
				SmartDeviceLinkProxyConfigurationResources, 
				/*enable advanced lifecycle management*/false, 
				/*app name*/ null,
				/*ngn media screen app name*/null,
				/*vr synonyms*/null,
				/*is media app*/ null,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				/*callbackToUIThread*/ true);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxy instance passing in: IProxyListener, SmartDeviceLinkProxyConfigurationResources.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param callbackToUIThread - If true, all callbacks will occur on the UI thread.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxy(IProxyListener listener, boolean callbackToUIThread) throws SmartDeviceLinkException {
		super(	listener,  
				/*SmartDeviceLink proxy configuration resources*/null,
				/*enable advanced lifecycle management*/false, 
				/*app name*/ null,
				/*ngn media screen app name*/null,
				/*vr synonyms*/null,
				/*is media app*/ null,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				callbackToUIThread);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxy instance passing in: IProxyListener, callBackToUIThread.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink.
	 * @param applicationContext - Context of the application. Used to access application specific resources. 
	 * @param callbackToUIThread - If true, all callbacks will occur on the UI thread.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxy(IProxyListener listener, SmartDeviceLinkProxyConfigurationResources SmartDeviceLinkProxyConfigurationResources, 
			boolean callbackToUIThread) throws SmartDeviceLinkException {
		super(	listener,  
				SmartDeviceLinkProxyConfigurationResources,
				/*enable advanced lifecycle management*/false, 
				/*app name*/ null,
				/*ngn media screen app name*/null,
				/*vr synonyms*/null,
				/*is media app*/ null,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				callbackToUIThread);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxy instance passing in: IProxyListener, callBackToUIThread.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	
	
	
	/******************** Public Helper Methods *************************/
	
	
	/**
	 *  Sends a RegisterAppInterface RPCRequest to SmartDeviceLink. Responses are captured through callback on IProxyListener.
	 *  
	 *  @param SyncMsgVersion
	 *  @param appName
	 *  @param ngnMediaScreenAppName
	 *  @param vrSynonyms
	 *  @param isMediaApp
	 *  @param languageDesired
	 *  @param autoActivateID
	 *  @param correlationID
	 *  
	 *  @throws SmartDeviceLinkException
	 */
	public void registerAppInterface(
			SyncMsgVersion SyncMsgVersion, String appName, String ngnMediaScreenAppName,
			Vector<String> vrSynonyms, Boolean isMediaApp, Language languageDesired, 
			String autoActivateID, Integer correlationID) 
			throws SmartDeviceLinkException {
		
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This SmartDeviceLinkProxy object has been disposed, it is no long capable of sending requests.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		registerAppInterfacePrivate(
				SyncMsgVersion, 
				appName,
				ngnMediaScreenAppName,
				vrSynonyms,
				isMediaApp, 
				languageDesired,
				autoActivateID,
				correlationID);
	}
	
	/**
	 * Sends a RegisterAppInterface RPCRequest to SmartDeviceLink. Responses are captured through callback on IProxyListener.
	 * 
	 * @param appName
	 * @param isMediaApp
	 * @param autoActivateID
	 * @throws SmartDeviceLinkException
	 */
	public void registerAppInterface(
			String appName, Boolean isMediaApp, String autoActivateID, Integer correlationID) 
			throws SmartDeviceLinkException {
		
		registerAppInterface(
				/*SyncMsgVersion*/null, 
				appName,
				/*ngnMediaScreenAppName*/null,
				/*vrSynonyms*/null,
				isMediaApp, 
				/*languageDesired*/null,
				autoActivateID,
				correlationID);
	}
	
	/**
	 * Sends a RegisterAppInterface RPCRequest to SmartDeviceLink. Responses are captured through callback on IProxyListener.
	 * 
	 * @param appName
	 * @throws SmartDeviceLinkException
	 */
	public void registerAppInterface(String appName, Integer correlationID) 
			throws SmartDeviceLinkException {
		
		registerAppInterface(appName, false, "", correlationID);
	}
	
	/**
	 * Sends an UnregisterAppInterface RPCRequest to SmartDeviceLink. Responses are captured through callback on IProxyListener.
	 * 
	 * @param correlationID
	 * @throws SmartDeviceLinkException
	 */
	public void unregisterAppInterface(Integer correlationID) 
			throws SmartDeviceLinkException {		
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This SmartDeviceLinkProxy object has been disposed, it is no long capable of executing methods.", 
										SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}		
				
		unregisterAppInterfacePrivate(correlationID);
	}
	
	/**
	 * Returns is isConnected state of the SmartDeviceLink transport.
	 * 
	 * @return Boolean isConnected
	 */
	public Boolean getIsConnected() {
		return super.getIsConnected();
	}
}
