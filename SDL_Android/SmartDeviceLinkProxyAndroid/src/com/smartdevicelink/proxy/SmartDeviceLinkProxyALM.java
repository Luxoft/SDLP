//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy;

import java.util.Vector;

import com.smartdevicelink.exception.SmartDeviceLinkException;
import com.smartdevicelink.exception.SmartDeviceLinkExceptionCause;
import com.smartdevicelink.proxy.interfaces.IProxyListenerALM;
import com.smartdevicelink.proxy.rpc.ButtonCapabilities;
import com.smartdevicelink.proxy.rpc.DisplayCapabilities;
import com.smartdevicelink.proxy.rpc.SyncMsgVersion;
import com.smartdevicelink.proxy.rpc.enums.HmiZoneCapabilities;
import com.smartdevicelink.proxy.rpc.enums.Language;
import com.smartdevicelink.proxy.rpc.enums.SpeechCapabilities;
import com.smartdevicelink.proxy.rpc.enums.SmartDeviceLinkDisconnectedReason;
import com.smartdevicelink.proxy.rpc.enums.VrCapabilities;
import com.smartdevicelink.trace.SyncTrace;
import com.smartdevicelink.transport.BaseTransportConfig;

public class SmartDeviceLinkProxyALM extends SmartDeviceLinkProxyBase<IProxyListenerALM> {
	
	private static final String SMARTDEVICELINK_LIB_TRACE_KEY = "42baba60-eb57-11df-98cf-0800200c9a66";
	private static final String SMARTDEVICELINK_LIB_PRIVATE_TOKEN = "{DAE1A88C-6C16-4768-ACA5-6F1247EA01C2}";
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink
	 * 
	 * Takes advantage of the advanced lifecycle management.
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param appName - Name of the application displayed on SmartDeviceLink. 
	 * @param isMediaApp - Indicates if the app is a media application.
	 */
	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, String appName, Boolean isMediaApp) throws SmartDeviceLinkException {
		super(	listener, 
				/*SmartDeviceLink proxy configuration resources*/null, 
				/*enable advanced lifecycle management*/true, 
				appName,
				/*ngn media app*/null,
				/*vr synonyms*/null,
				/*is media app*/isMediaApp,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				/*callbackToUIThread*/ false);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, appName, and isMediaApp.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}

	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, String appName, Boolean isMediaApp,
			BaseTransportConfig transportConfig) throws SmartDeviceLinkException {
		super(	listener, 
				/*SmartDeviceLink proxy configuration resources*/null, 
				/*enable advanced lifecycle management*/true, 
				appName,
				/*ngn media app*/null,
				/*vr synonyms*/null,
				/*is media app*/isMediaApp,
				/*SyncMsgVersion*/null,
				/*language desired*/null,
				/*autoActivateID*/null,
				/*callbackToUIThread*/ false,
				transportConfig);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, appName, and isMediaApp.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * Takes advantage of the advanced lifecycle management. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param appName - Name of the application displayed on SmartDeviceLink. 
	 * @param ngnMediaScreenAppName - Name of the application displayed on SmartDeviceLink for Navigation equipped 
	 * vehicles. Limited to five characters. 
	 * @param vrSynonyms - A vector of strings, all of which can be used as voice commands to 
	 * @param isMediaApp - Indicates if the app is a media application.
	 * @param SyncMsgVersion - Indicates the version of SmartDeviceLink SmartDeviceLink Messages desired. Must be less than
	 * or equal to the version of SmartDeviceLink SmartDeviceLink running on the vehicle. 
	 * @param languageDesired - Indicates the language desired for the SmartDeviceLink interface.
	 * @param autoActivateID - ID used to re-register previously registered application.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, String appName, String ngnMediaScreenAppName, 
			Vector<String> vrSynonyms, Boolean isMediaApp, SyncMsgVersion SyncMsgVersion, 
			Language languageDesired, String autoActivateID) throws SmartDeviceLinkException {
		super(	listener, 
				/*SmartDeviceLink proxy configuration resources*/null, 
				/*enable advanced lifecycle management*/true, 
				appName,
				ngnMediaScreenAppName,
				vrSynonyms,
				isMediaApp,
				SyncMsgVersion,
				languageDesired,
				autoActivateID,
				/*callbackToUIThread*/ false);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, appName, ngnMediaScreenAppName, " +
				"vrSynonyms, isMediaApp, SyncMsgVersion, languageDesired, and autoActivateID.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * Takes advantage of the advanced lifecycle management. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param applicationContext - Context of the application. Used to access application specific resources.
	 * @param appName - Name of the application displayed on SmartDeviceLink. 
	 * @param ngnMediaScreenAppName - Name of the application displayed on SmartDeviceLink for Navigation equipped 
	 * vehicles. Limited to five characters. 
	 * @param vrSynonyms - A vector of strings, all of which can be used as voice commands to 
	 * @param isMediaApp - Indicates if the app is a media application.
	 * @param SyncMsgVersion - Indicates the version of SmartDeviceLink SmartDeviceLink Messages desired. Must be less than
	 * or equal to the version of SmartDeviceLink SmartDeviceLink running on the vehicle. 
	 * @param languageDesired - Indicates the language desired for the SmartDeviceLink interface.
	 * @param autoActivateID - ID used to re-register previously registered application.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, SmartDeviceLinkProxyConfigurationResources SmartDeviceLinkProxyConfigurationResources, 
			String appName, String ngnMediaScreenAppName, Vector<String> vrSynonyms, 
			Boolean isMediaApp, SyncMsgVersion SyncMsgVersion, Language languageDesired, 
			String autoActivateID) throws SmartDeviceLinkException {
		super(	listener, 
				SmartDeviceLinkProxyConfigurationResources, 
				/*enable advanced lifecycle management*/true, 
				appName,
				ngnMediaScreenAppName,
				vrSynonyms,
				isMediaApp,
				SyncMsgVersion,
				languageDesired,
				autoActivateID,
				/*callbackToUIThread*/ false);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, SmartDeviceLinkProxyConfigurationResources, " +
				"appName, ngnMediaScreenAppName, vrSynonyms, isMediaApp, SyncMsgVersion, languageDesired, and autoActivateID.", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * Takes advantage of the advanced lifecycle management. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param appName - Name of the application displayed on SmartDeviceLink. 
	 * @param ngnMediaScreenAppName - Name of the application displayed on SmartDeviceLink for Navigation equipped 
	 * vehicles. Limited to five characters. 
	 * @param vrSynonyms - A vector of strings, all of which can be used as voice commands to 
	 * @param isMediaApp - Indicates if the app is a media application.
	 * @param SyncMsgVersion - Indicates the version of SmartDeviceLink SmartDeviceLink Messages desired. Must be less than
	 * or equal to the version of SmartDeviceLink SmartDeviceLink running on the vehicle. 
	 * @param languageDesired - Indicates the language desired for the SmartDeviceLink interface.
	 * @param autoActivateID - ID used to re-register previously registered application.
	 * @param callbackToUIThread - If true, all callbacks will occur on the UI thread.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, String appName, String ngnMediaScreenAppName, 
			Vector<String> vrSynonyms, Boolean isMediaApp, SyncMsgVersion SyncMsgVersion, 
			Language languageDesired, String autoActivateID, boolean callbackToUIThread) throws SmartDeviceLinkException {
		super(	listener, 
				/*SmartDeviceLink proxy configuration resources*/null,
				/*enable advanced lifecycle management*/true, 
				appName,
				ngnMediaScreenAppName,
				vrSynonyms,
				isMediaApp,
				SyncMsgVersion,
				languageDesired,
				autoActivateID,
				callbackToUIThread);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, " +
				"appName, ngnMediaScreenAppName, vrSynonyms, isMediaApp, SyncMsgVersion, languageDesired, autoActivateID, " +
				"and callbackToUIThread", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	/**
	 * Constructor for the SmartDeviceLinkProxy object, the proxy for communicating between the App and SmartDeviceLink.
	 * 
	 * Takes advantage of the advanced lifecycle management. 
	 * 
	 * @param listener - Reference to the object in the App listening to callbacks from SmartDeviceLink. 
	 * @param applicationContext - Context of the application. Used to access application specific resources.
	 * @param appName - Name of the application displayed on SmartDeviceLink. 
	 * @param ngnMediaScreenAppName - Name of the application displayed on SmartDeviceLink for Navigation equipped 
	 * vehicles. Limited to five characters. 
	 * @param vrSynonyms - A vector of strings, all of which can be used as voice commands to 
	 * @param isMediaApp - Indicates if the app is a media application.
	 * @param SyncMsgVersion - Indicates the version of SmartDeviceLink SmartDeviceLink Messages desired. Must be less than
	 * or equal to the version of SmartDeviceLink SmartDeviceLink running on the vehicle. 
	 * @param languageDesired - Indicates the language desired for the SmartDeviceLink interface.
	 * @param autoActivateID - ID used to re-register previously registered application.
	 * @param callbackToUIThread - If true, all callbacks will occur on the UI thread.
	 * @throws SmartDeviceLinkException
	 */
	public SmartDeviceLinkProxyALM(IProxyListenerALM listener, SmartDeviceLinkProxyConfigurationResources SmartDeviceLinkProxyConfigurationResources, 
			String appName, String ngnMediaScreenAppName, Vector<String> vrSynonyms, Boolean isMediaApp, 
			SyncMsgVersion SyncMsgVersion, Language languageDesired, String autoActivateID, 
			boolean callbackToUIThread) throws SmartDeviceLinkException {
		super(	listener, 
				SmartDeviceLinkProxyConfigurationResources,
				/*enable advanced lifecycle management*/true, 
				appName,
				ngnMediaScreenAppName,
				vrSynonyms,
				isMediaApp,
				SyncMsgVersion,
				languageDesired,
				autoActivateID,
				callbackToUIThread);
		
		SyncTrace.logProxyEvent("Application constructed SmartDeviceLinkProxyALM instance passing in: IProxyListener, SmartDeviceLinkProxyConfigurationResources, " +
				"appName, ngnMediaScreenAppName, vrSynonyms, isMediaApp, SyncMsgVersion, languageDesired, autoActivateID, " +
				"and callbackToUIThread", SMARTDEVICELINK_LIB_TRACE_KEY);
	}
	
	// Allow applications using ALM to reset the proxy (dispose and reinstantiate)
	/**
	 * Disconnects the application from SmartDeviceLink, then recreates the transport such that
	 * the next time a SmartDeviceLink unit discovers applications, this application will be
	 * available.
	 */
	public void resetProxy() throws SmartDeviceLinkException {
		super.cycleProxy(SmartDeviceLinkDisconnectedReason.APPLICATION_REQUESTED_DISCONNECT);
	}
	
	/********* Getters for values returned by RegisterAppInterfaceResponse **********/
	
	/**
	 * Gets autoActivateId set when application interface is registered.
	 * 
	 * @return autoActivateId 
	 * @throws SmartDeviceLinkException
	 */
	public String getAutoActivateId() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is not connected. Unable to get the autoActivateId.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _autoActivateIdReturned;
	}
	
	/**
	 * Gets buttonCapabilities set when application interface is registered.
	 * 
	 * @return buttonCapabilities
	 * @throws SmartDeviceLinkException
	 */
	public Vector<ButtonCapabilities> getButtonCapabilities() throws SmartDeviceLinkException{
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the buttonCapabilities.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _buttonCapabilities;
	}
	
	/**
	 * Gets displayCapabilities set when application interface is registered.
	 * 
	 * @return displayCapabilities
	 * @throws SmartDeviceLinkException
	 */
	public DisplayCapabilities getDisplayCapabilities() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the displayCapabilities.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _displayCapabilities;
	}
	
	/**
	 * Gets hmiZoneCapabilities set when application interface is registered.
	 * 
	 * @return hmiZoneCapabilities
	 * @throws SmartDeviceLinkException
	 */
	public Vector<HmiZoneCapabilities> getHmiZoneCapabilities() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the hmiZoneCapabilities.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _hmiZoneCapabilities;
	}
	
	/**
	 * Gets speechCapabilities set when application interface is registered.
	 * 
	 * @return speechCapabilities
	 * @throws SmartDeviceLinkException
	 */
	public Vector<SpeechCapabilities> getSpeechCapabilities() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the speechCapabilities.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		
		return _speechCapabilities;
	}
	
	/**
	 * Gets SmartDeviceLinkLanguage set when application interface is registered.
	 * 
	 * @return SmartDeviceLinkLanguage
	 * @throws SmartDeviceLinkException
	 */
	public Language getSmartDeviceLinkLanguage() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the SmartDeviceLinkLanguage.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _SmartDeviceLinkLanguage;
	}
	
	/**
	 * Gets SyncMsgVersion set when application interface is registered.
	 * 
	 * @return SyncMsgVersion
	 * @throws SmartDeviceLinkException
	 */
	public SyncMsgVersion getSyncMsgVersion() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the SyncMsgVersion.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _SyncMsgVersion;
	}
	
	/**
	 * Gets vrCapabilities set when application interface is registered.
	 * 
	 * @return vrCapabilities
	 * @throws SmartDeviceLinkException
	 */
	public Vector<VrCapabilities> getVrCapabilities() throws SmartDeviceLinkException {
		// Test if proxy has been disposed
		if (_proxyDisposed) {
			throw new SmartDeviceLinkException("This object has been disposed, it is no long capable of executing methods.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_DISPOSED);
		}
		
		// Test SmartDeviceLink availability 
		if (!_appInterfaceRegisterd) {
			throw new SmartDeviceLinkException("SmartDeviceLink is unavailable. Unable to get the vrCapabilities.", SmartDeviceLinkExceptionCause.SMARTDEVICELINK_UNAVAILALBE);
		}
		return _vrCapabilities;
	}
}
