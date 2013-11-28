//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.android.service;

import java.util.Arrays;
import java.util.Vector;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.util.Pair;
import android.widget.Toast;

import com.smartdevicelink.android.R;
import com.smartdevicelink.android.activity.SmartDeviceLinkTester;
import com.smartdevicelink.android.adapters.logAdapter;
import com.smartdevicelink.android.constants.Const;
import com.smartdevicelink.android.module.ModuleTest;
import com.smartdevicelink.android.receivers.SmartDeviceLinkReceiver;
import com.smartdevicelink.exception.SmartDeviceLinkException;
import com.smartdevicelink.exception.SmartDeviceLinkExceptionCause;
import com.smartdevicelink.proxy.RPCStruct;
import com.smartdevicelink.proxy.SmartDeviceLinkProxyALM;
import com.smartdevicelink.proxy.interfaces.IProxyListenerALM;
import com.smartdevicelink.proxy.rpc.AddCommandResponse;
import com.smartdevicelink.proxy.rpc.AddSubMenuResponse;
import com.smartdevicelink.proxy.rpc.AlertResponse;
import com.smartdevicelink.proxy.rpc.CreateInteractionChoiceSetResponse;
import com.smartdevicelink.proxy.rpc.DeleteCommandResponse;
import com.smartdevicelink.proxy.rpc.DeleteInteractionChoiceSetResponse;
import com.smartdevicelink.proxy.rpc.DeleteSubMenuResponse;
import com.smartdevicelink.proxy.rpc.EncodedSyncPDataResponse;
import com.smartdevicelink.proxy.rpc.GenericResponse;
import com.smartdevicelink.proxy.rpc.OnButtonEvent;
import com.smartdevicelink.proxy.rpc.OnButtonPress;
import com.smartdevicelink.proxy.rpc.OnCommand;
import com.smartdevicelink.proxy.rpc.OnDriverDistraction;
import com.smartdevicelink.proxy.rpc.OnEncodedSyncPData;
import com.smartdevicelink.proxy.rpc.OnHMIStatus;
import com.smartdevicelink.proxy.rpc.OnPermissionsChange;
import com.smartdevicelink.proxy.rpc.OnTBTClientState;
import com.smartdevicelink.proxy.rpc.PerformInteractionResponse;
import com.smartdevicelink.proxy.rpc.ResetGlobalPropertiesResponse;
import com.smartdevicelink.proxy.rpc.SetGlobalPropertiesResponse;
import com.smartdevicelink.proxy.rpc.SetMediaClockTimerResponse;
import com.smartdevicelink.proxy.rpc.ShowResponse;
import com.smartdevicelink.proxy.rpc.SpeakResponse;
import com.smartdevicelink.proxy.rpc.SubscribeButtonResponse;
import com.smartdevicelink.proxy.rpc.UnsubscribeButtonResponse;
import com.smartdevicelink.proxy.rpc.enums.ButtonName;
import com.smartdevicelink.proxy.rpc.enums.Result;
import com.smartdevicelink.proxy.rpc.pm.AddProfileResponse;
import com.smartdevicelink.proxy.rpc.pm.AppStateChangedResponse;
import com.smartdevicelink.proxy.rpc.pm.LoadProfileResponse;
import com.smartdevicelink.proxy.rpc.pm.OnProfileClosed;
import com.smartdevicelink.proxy.rpc.pm.OnProfileStateChanged;
import com.smartdevicelink.proxy.rpc.pm.OnSendProfileToAppMessage;
import com.smartdevicelink.proxy.rpc.pm.RemoveProfileResponse;
import com.smartdevicelink.proxy.rpc.pm.SendAppToProfileMessageResponse;
import com.smartdevicelink.proxy.rpc.pm.UnloadProfileResponse;
import com.smartdevicelink.transport.TCPTransportConfig;

public class ProxyService extends Service implements IProxyListenerALM {	
	static final String TAG = "SmartDeviceLinkTester";
	private Integer autoIncCorrId = 1;

	private static SmartDeviceLinkTester _mainInstance;	
	private static ProxyService _instance;
	private static SmartDeviceLinkProxyALM _SmartDeviceLinkProxy;
	private static logAdapter _msgAdapter;
	private ModuleTest _testerMain;
	private BluetoothAdapter mBtAdapter;
	private MediaPlayer embeddedAudioPlayer;
	private Boolean playingAudio = false;
	protected SmartDeviceLinkReceiver mediaButtonReceiver;
	
	private boolean firstHMIStatusChange = true;
	
	private static boolean waitingForResponse = false;
	
	public void onCreate() {
		super.onCreate();
		
		IntentFilter mediaIntentFilter = new IntentFilter();
		mediaIntentFilter.addAction(Intent.ACTION_MEDIA_BUTTON);
		
		mediaButtonReceiver = new SmartDeviceLinkReceiver();
		registerReceiver(mediaButtonReceiver, mediaIntentFilter);
		
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.onCreate()", Log.INFO);
		else Log.i(TAG, "ProxyService.onCreate()");
		
		_instance = this;
	}
	
	public void showLockMain() {
		if(SmartDeviceLinkTester.getInstance() == null) {
			Intent i = new Intent(this, SmartDeviceLinkTester.class);
			i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			startActivity(i);
		}		
	}
	
	public int onStartCommand(Intent intent, int flags, int startId) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.onStartCommand()", Log.INFO);
		else Log.i(TAG, "ProxyService.onStartCommand()");
		
		startProxyIfNetworkConnected();
		
        setCurrentActivity(SmartDeviceLinkTester.getInstance());
			
        return START_STICKY;
	}

	private void startProxyIfNetworkConnected() {
		final SharedPreferences prefs = getSharedPreferences(Const.PREFS_NAME,
				MODE_PRIVATE);
		final int transportType = prefs.getInt(
				Const.Transport.PREFS_KEY_TRANSPORT_TYPE,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_TYPE);

		if (transportType == Const.Transport.KEY_BLUETOOTH) {
			Log.d(TAG, "ProxyService. onStartCommand(). Transport = Bluetooth.");
			mBtAdapter = BluetoothAdapter.getDefaultAdapter();
			if (mBtAdapter != null) {
				if (mBtAdapter.isEnabled()) {
					startProxy();
				}
			}
		} else {
			startProxy();
		}
	}

	public void startProxy() {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.startProxy()", true);
		else Log.i(TAG, "ProxyService.startProxy()");
		
		if (_SmartDeviceLinkProxy == null) {
			try {
				SharedPreferences settings = getSharedPreferences(
						Const.PREFS_NAME, 0);
				boolean isMediaApp = settings.getBoolean(
						Const.PREFS_KEY_ISMEDIAAPP,
						Const.PREFS_DEFAULT_ISMEDIAAPP);
				String appName = settings.getString(Const.PREFS_KEY_APPNAME,
						Const.PREFS_DEFAULT_APPNAME);
				int transportType = settings.getInt(
						Const.Transport.PREFS_KEY_TRANSPORT_TYPE,
						Const.Transport.PREFS_DEFAULT_TRANSPORT_TYPE);
				String ipAddress = settings.getString(
						Const.Transport.PREFS_KEY_TRANSPORT_IP,
						Const.Transport.PREFS_DEFAULT_TRANSPORT_IP);
				int tcpPort = settings.getInt(
						Const.Transport.PREFS_KEY_TRANSPORT_PORT,
						Const.Transport.PREFS_DEFAULT_TRANSPORT_PORT);
				boolean autoReconnect = settings
						.getBoolean(
								Const.Transport.PREFS_KEY_TRANSPORT_RECONNECT,
								Const.Transport.PREFS_DEFAULT_TRANSPORT_RECONNECT_DEFAULT);

				if (transportType == Const.Transport.KEY_BLUETOOTH) {
					_SmartDeviceLinkProxy = new SmartDeviceLinkProxyALM(this, appName, isMediaApp);
				} else {
					_SmartDeviceLinkProxy = new SmartDeviceLinkProxyALM(this, appName, isMediaApp,
							new TCPTransportConfig(tcpPort, ipAddress, autoReconnect));
				}
			} catch (SmartDeviceLinkException e) {
				e.printStackTrace();
				//error creating proxy, returned proxy = null
				if (_SmartDeviceLinkProxy == null){
					stopSelf();
				}
			}
		}
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.startProxy() returning", Log.INFO);
		else Log.i(TAG, "ProxyService.startProxy() returning");
	}
	
	public void onDestroy() {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.onDestroy()", Log.INFO);
		else Log.i(TAG, "ProxyService.onDestroy()");
		
		disposeSmartDeviceLinkProxy();
		_instance = null;
		if (embeddedAudioPlayer != null) embeddedAudioPlayer.release();		
		unregisterReceiver(mediaButtonReceiver);	
		super.onDestroy();
	}
	
	public void disposeSmartDeviceLinkProxy() {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("ProxyService.disposeSmartDeviceLinkProxy()", Log.INFO);
		else Log.i(TAG, "ProxyService.disposeSmartDeviceLinkProxy()");
		
		if (_SmartDeviceLinkProxy != null) {
			try {
				_SmartDeviceLinkProxy.dispose();
			} catch (SmartDeviceLinkException e) {
				e.printStackTrace();
			}
			_SmartDeviceLinkProxy = null;
		}
	}
	
	private void initialize() {
		playingAudio = true;
		playAnnoyingRepetitiveAudio();
		
		try {
			_SmartDeviceLinkProxy.show("SmartDeviceLink", "Tester", null, null, null, null, nextCorrID());
		} catch (SmartDeviceLinkException e) {
			if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
			if (_msgAdapter != null) _msgAdapter.logMessage("Error sending show", Log.ERROR, e, true);
			else Log.e(TAG, "Error sending show", e);
		}

		try { 
			_SmartDeviceLinkProxy.subscribeButton(ButtonName.OK, nextCorrID());
			_SmartDeviceLinkProxy.subscribeButton(ButtonName.SEEKLEFT, nextCorrID());
			_SmartDeviceLinkProxy.subscribeButton(ButtonName.SEEKRIGHT, nextCorrID());
			_SmartDeviceLinkProxy.subscribeButton(ButtonName.TUNEUP, nextCorrID());
			_SmartDeviceLinkProxy.subscribeButton(ButtonName.TUNEDOWN, nextCorrID());
			Vector<ButtonName> buttons = new Vector<ButtonName>(Arrays.asList(new ButtonName[] {
					ButtonName.OK, ButtonName.SEEKLEFT, ButtonName.SEEKRIGHT, ButtonName.TUNEUP,
					ButtonName.TUNEDOWN }));
			SmartDeviceLinkTester.getInstance().buttonsSubscribed(buttons);
		} catch (SmartDeviceLinkException e) {
			if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
			if (_msgAdapter != null) _msgAdapter.logMessage("Error subscribing to buttons", Log.ERROR, e, true);
			else Log.e(TAG, "Error subscribing to buttons", e);
		}

		
		try {
			_SmartDeviceLinkProxy.addCommand(100, "XML Test", new Vector<String>(Arrays.asList(new String[] {"XML Test", "XML"})), nextCorrID());
		} catch (SmartDeviceLinkException e) {
			if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
			if (_msgAdapter != null) _msgAdapter.logMessage("Error adding AddCommands", Log.ERROR, e, true);
			else Log.e(TAG, "Error adding AddCommands", e);
		}
	}
	
	public void playPauseAnnoyingRepetitiveAudio() {
		if (embeddedAudioPlayer != null && embeddedAudioPlayer.isPlaying()) {
			playingAudio = false;
			pauseAnnoyingRepetitiveAudio();
		} else {
			playingAudio = true;
			playAnnoyingRepetitiveAudio();
		}
	}

	private void playAnnoyingRepetitiveAudio() {
		if (embeddedAudioPlayer == null) {
			embeddedAudioPlayer = MediaPlayer.create(this, R.raw.arco);
			embeddedAudioPlayer.setLooping(true);
		}
		embeddedAudioPlayer.start();
		
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("Playing audio", true);
		else Log.i(TAG, "Playing audio");
	}
	
	public void pauseAnnoyingRepetitiveAudio() {
		if (embeddedAudioPlayer != null && embeddedAudioPlayer.isPlaying()) {
			embeddedAudioPlayer.pause();
			
			if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
			if (_msgAdapter != null) _msgAdapter.logMessage("Paused audio", true);
			else Log.i(TAG, "Paused audio");
		}
	}
	
	public static SmartDeviceLinkProxyALM getProxyInstance() {
		return _SmartDeviceLinkProxy;
	}

	public static ProxyService getInstance() {
		return _instance;
	}
	
	public SmartDeviceLinkTester getCurrentActivity() {
		return _mainInstance;
	}

	public void startModuleTest() {
		_testerMain = new ModuleTest();
	}
	
	public static void waiting(boolean waiting) {
		waitingForResponse = waiting;
	}

	public void setCurrentActivity(SmartDeviceLinkTester currentActivity) {
		if (this._mainInstance != null) {
			this._mainInstance.finish();
			this._mainInstance = null;
		}
		
		this._mainInstance = currentActivity;
		// update the _msgAdapter
		_msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
	}
	
	protected int nextCorrID() {
		autoIncCorrId++;
		return autoIncCorrId;
	}

	@Override
	public void onOnHMIStatus(OnHMIStatus notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);

		switch(notification.getSystemContext()) {
			case SYSCTXT_MAIN:
				break;
			case SYSCTXT_VRSESSION:
				break;
			case SYSCTXT_MENU:
				break;
			default:
				return;
		}
		
		switch(notification.getAudioStreamingState()) {
			case AUDIBLE:
				if (playingAudio) playAnnoyingRepetitiveAudio();
				break;
			case NOT_AUDIBLE:
				pauseAnnoyingRepetitiveAudio();
				break;
			default:
				return;
		}
		
		switch(notification.getHmiLevel()) {
			case HMI_FULL:
				if (notification.getFirstRun()) {
					showLockMain();
					_testerMain = new ModuleTest();
					_testerMain = ModuleTest.getModuleTestInstance();
					initialize();
				}
				else {
					try {
						if (!waitingForResponse && _testerMain.getThreadContext() != null) {
							_SmartDeviceLinkProxy.show("SmartDeviceLink Proxy", "Tester Ready", null, null, null, null, nextCorrID());
						}
					} catch (SmartDeviceLinkException e) {
						if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
						if (_msgAdapter != null) _msgAdapter.logMessage("Error sending show", Log.ERROR, e, true);
						else Log.e(TAG, "Error sending show", e);
					}
				}
				break;
			case HMI_LIMITED:
				break;
			case HMI_BACKGROUND:
				break;
			case HMI_NONE:
				break;
			default:
				return;
		}
	}
	
	@Override
	public void onOnCommand(OnCommand notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
		
		switch(notification.getCmdID())
		{
			case 100: //XML Test
				_testerMain.restart();
				break;
			default:
				break;
		}
	}

	@Override
	public void onProxyClosed(String info, Exception e) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("onProxyClosed: " + info, Log.ERROR, e);
		else Log.e(TAG, "onProxyClosed: " + info, e);
		
		boolean wasConnected = !firstHMIStatusChange;
		firstHMIStatusChange = true;
		
		if (wasConnected) {
			final SmartDeviceLinkTester mainActivity = SmartDeviceLinkTester.getInstance();
			if (mainActivity != null) {
				mainActivity.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						mainActivity.onProxyClosed();
					}
				});
			} else {
				Log.w(TAG, "mainActivity not found");
			}
		}
		
		if(((SmartDeviceLinkException) e).getSmartDeviceLinkExceptionCause() != SmartDeviceLinkExceptionCause.SMARTDEVICELINK_PROXY_CYCLED
				&& ((SmartDeviceLinkException) e).getSmartDeviceLinkExceptionCause() != SmartDeviceLinkExceptionCause.BLUETOOTH_DISABLED) {
			reset();
		}
	}
	
	public void reset(){
	   try {
		   if (_SmartDeviceLinkProxy != null) _SmartDeviceLinkProxy.resetProxy();
           else startProxyIfNetworkConnected();
		} catch (SmartDeviceLinkException e1) {
			e1.printStackTrace();
			//something goes wrong, & the proxy returns as null, stop the service.
			//do not want a running service with a null proxy
			if (_SmartDeviceLinkProxy == null){
				stopSelf();
			}
		}
	}
	
	/**
	 * Restarting SmartDeviceLinkProxyALM. For example after changing transport type
	 */
	public void restart() {
		Log.i(TAG, "ProxyService.Restart SmartDeviceLinkProxyALM.");
		disposeSmartDeviceLinkProxy();
		startProxyIfNetworkConnected();
	}
	
	@Override
	public void onError(String info, Exception e) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
 		if (_msgAdapter != null) {
 			_msgAdapter.logMessage("******onProxyError******", Log.ERROR);
 			_msgAdapter.logMessage("ERROR: " + info, Log.ERROR, e);
		} else {
			Log.e(TAG, "******onProxyError******");
			Log.e(TAG, "ERROR: " + info, e);
 		}
	}
	
	/*********************************
	** SmartDeviceLink SmartDeviceLink Base Callback's **
	*********************************/
	@Override
	public void onAddSubMenuResponse(AddSubMenuResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onCreateInteractionChoiceSetResponse(CreateInteractionChoiceSetResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		final SmartDeviceLinkTester mainActivity = SmartDeviceLinkTester.getInstance();
		final boolean success = response.getSuccess();
		mainActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mainActivity.onCreateChoiceSetResponse(success);
			}
		});
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onDeleteCommandResponse(DeleteCommandResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onDeleteInteractionChoiceSetResponse(DeleteInteractionChoiceSetResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onDeleteSubMenuResponse(DeleteSubMenuResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onEncodedSyncPDataResponse(EncodedSyncPDataResponse response) {
		Log.i("SmartDeviceLinkp", response.getInfo() + response.getResultCode() + response.getSuccess());
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onResetGlobalPropertiesResponse(ResetGlobalPropertiesResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onSetMediaClockTimerResponse(SetMediaClockTimerResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onSpeakResponse(SpeakResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onSubscribeButtonResponse(SubscribeButtonResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onUnsubscribeButtonResponse(UnsubscribeButtonResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onOnDriverDistraction(OnDriverDistraction notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
	}
	@Override
	public void onGenericResponse(GenericResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onOnButtonEvent(OnButtonEvent notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
	}
	@Override
	public void onOnButtonPress(OnButtonPress notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
		
		switch(notification.getButtonName())
		{
			case OK:
				playPauseAnnoyingRepetitiveAudio();
				break;
			case SEEKLEFT:
				break;
			case SEEKRIGHT:
				break;
			case TUNEUP:
				break;
			case TUNEDOWN:
				break;
			default:
				break;
		}
	}
	
	/*********************************
	** SmartDeviceLink SmartDeviceLink Updated Callback's **
	*********************************/
	@Override
	public void onAddCommandResponse(AddCommandResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onAlertResponse(AlertResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}	
	@Override
	public void onPerformInteractionResponse(PerformInteractionResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onSetGlobalPropertiesResponse(SetGlobalPropertiesResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onShowResponse(ShowResponse response) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(response, true);
		else Log.i(TAG, "" + response);
		
		if (waitingForResponse && _testerMain.getThreadContext() != null) {
			ModuleTest.responses.add(new Pair<Integer, Result>(response.getCorrelationID(), response.getResultCode()));
			synchronized (_testerMain.getThreadContext()) { _testerMain.getThreadContext().notify();};
		}
	}
	@Override
	public void onOnTBTClientState(OnTBTClientState notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
	}

	/*********************************
	** SmartDeviceLink SmartDeviceLink Policies Callback's **
	*********************************/
	@Override
	public void onOnPermissionsChange(OnPermissionsChange notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
	}
	@Override
	public void onOnEncodedSyncPData(OnEncodedSyncPData notification) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage(notification, true);
		else Log.i(TAG, "" + notification);
	}
	@Override
	public IBinder onBind(Intent intent) {
		if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
		if (_msgAdapter != null) _msgAdapter.logMessage("Service on Bind");
		else Log.i(TAG, "Service on Bind");
		return new Binder();
	}

    /*********************************
    ** SDLP Profile Manager Callbacks **
    *********************************/
    @Override
    public void onAddProfileResponse(AddProfileResponse response) {
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onRemoveProfileResponse(RemoveProfileResponse response) {
        logProfileManagerEvent(response);
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onLoadProfileReponse(LoadProfileResponse response) {
        logProfileManagerEvent(response);
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onUnloadProfileResponse(UnloadProfileResponse response) {
        logProfileManagerEvent(response);
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onSendMessageToProfileResponse(SendAppToProfileMessageResponse response) {
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onAppStateChangedResponse(AppStateChangedResponse response) {
        logProfileManagerEvent(response);
        _mainInstance.handlePMMessage(response);
    }

    @Override
    public void onProfileClosed(OnProfileClosed notification) {
        logProfileManagerEvent(notification);
        _mainInstance.handlePMMessage(notification);
		try {
			_SmartDeviceLinkProxy.show("SmartDeviceLink", "Tester", null, null, null, null, nextCorrID());
		} catch (SmartDeviceLinkException e) {
			if (_msgAdapter == null) _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
			if (_msgAdapter != null) _msgAdapter.logMessage("Error sending show", Log.ERROR, e, true);
			else Log.e(TAG, "Error sending show", e);
		}
    }

    @Override
    public void onProfileStateChanged(final OnProfileStateChanged notification) {
        logProfileManagerEvent(notification);
        _mainInstance.handlePMMessage(notification);
        new Handler(Looper.getMainLooper()).post(new Runnable(){
            public void run(){
                Toast.makeText(ProxyService.this, 
                        "Profile state: " + notification.getState().toString(), Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    public void onReceiveMessageFromProfile(final OnSendProfileToAppMessage notification) {
        _mainInstance.handlePMMessage(notification);
        new Handler(Looper.getMainLooper()).post(new Runnable(){
            public void run(){
                Toast.makeText(ProxyService.this, 
                        "Received: " + new String(notification.getMessage()), Toast.LENGTH_LONG).show();
            }
        });        
    }

    private void logProfileManagerEvent(RPCStruct struct) {
        if (_msgAdapter == null) {
            _msgAdapter = SmartDeviceLinkTester.getMessageAdapter();
        }
        if (_msgAdapter != null) {
            _msgAdapter.logMessage(struct, true);
        }
    }
}
