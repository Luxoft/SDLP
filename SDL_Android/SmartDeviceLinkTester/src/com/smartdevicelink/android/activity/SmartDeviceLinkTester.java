//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.android.activity;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CheckedTextView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RadioGroup;
import android.widget.ScrollView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.smartdevicelink.android.R;
import com.smartdevicelink.android.adapters.logAdapter;
import com.smartdevicelink.android.constants.Const;
import com.smartdevicelink.android.constants.SmartDeviceLinkSubMenu;
import com.smartdevicelink.android.module.ModuleTest;
import com.smartdevicelink.android.pmtests.ProfileManagerTests;
import com.smartdevicelink.android.service.ProxyService;
import com.smartdevicelink.exception.SmartDeviceLinkException;
import com.smartdevicelink.marshal.JsonRPCMarshaller;
import com.smartdevicelink.proxy.RPCMessage;
import com.smartdevicelink.proxy.RPCRequest;
import com.smartdevicelink.proxy.RPCRequestFactory;
import com.smartdevicelink.proxy.RPCResponse;
import com.smartdevicelink.proxy.SmartDeviceLinkProxyALM;
import com.smartdevicelink.proxy.TTSChunkFactory;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.AddCommand;
import com.smartdevicelink.proxy.rpc.AddSubMenu;
import com.smartdevicelink.proxy.rpc.Alert;
import com.smartdevicelink.proxy.rpc.Choice;
import com.smartdevicelink.proxy.rpc.CreateInteractionChoiceSet;
import com.smartdevicelink.proxy.rpc.DeleteCommand;
import com.smartdevicelink.proxy.rpc.DeleteInteractionChoiceSet;
import com.smartdevicelink.proxy.rpc.DeleteSubMenu;
import com.smartdevicelink.proxy.rpc.EncodedSyncPData;
import com.smartdevicelink.proxy.rpc.MenuParams;
import com.smartdevicelink.proxy.rpc.PerformInteraction;
import com.smartdevicelink.proxy.rpc.ResetGlobalProperties;
import com.smartdevicelink.proxy.rpc.SetGlobalProperties;
import com.smartdevicelink.proxy.rpc.SetMediaClockTimer;
import com.smartdevicelink.proxy.rpc.Show;
import com.smartdevicelink.proxy.rpc.Speak;
import com.smartdevicelink.proxy.rpc.StartTime;
import com.smartdevicelink.proxy.rpc.SubscribeButton;
import com.smartdevicelink.proxy.rpc.TTSChunk;
import com.smartdevicelink.proxy.rpc.UnsubscribeButton;
import com.smartdevicelink.proxy.rpc.enums.ButtonName;
import com.smartdevicelink.proxy.rpc.enums.GlobalProperty;
import com.smartdevicelink.proxy.rpc.enums.InteractionMode;
import com.smartdevicelink.proxy.rpc.enums.Language;
import com.smartdevicelink.proxy.rpc.enums.MobileAppState;
import com.smartdevicelink.proxy.rpc.enums.ProfileState;
import com.smartdevicelink.proxy.rpc.enums.SpeechCapabilities;
import com.smartdevicelink.proxy.rpc.enums.UpdateMode;
import com.smartdevicelink.proxy.rpc.pm.AddProfile;
import com.smartdevicelink.proxy.rpc.pm.AppStateChanged;
import com.smartdevicelink.proxy.rpc.pm.LoadProfile;
import com.smartdevicelink.proxy.rpc.pm.RemoveProfile;
import com.smartdevicelink.proxy.rpc.pm.SendAppToProfileMessage;
import com.smartdevicelink.proxy.rpc.pm.UnloadProfile;
import com.smartdevicelink.tcpdiscovery.TcpDiscoverer;
import com.smartdevicelink.tcpdiscovery.TcpDiscovererCallbackDefaultImplDelegate;
import com.smartdevicelink.transport.TransportType;

public class SmartDeviceLinkTester extends Activity implements OnClickListener, TcpDiscovererCallbackDefaultImplDelegate {
	private static final String logTag = "SmartDeviceLinkTester";
	
	private static final String ButtonSubscriptions = "ButtonSubscriptions";

    private static SmartDeviceLinkTester _activity;
    private static ArrayList<Object> _logMessages = new ArrayList<Object>();
	private static logAdapter _msgAdapter;
	private static ProfileManagerTests _profileManagerTests;
	private ModuleTest _testerMain;
	
	private ScrollView _scroller = null;
	private ListView _listview = null;
	
	private ArrayAdapter<SmartDeviceLinkSubMenu> _submenuAdapter = null;
	private ArrayAdapter<Integer> _commandAdapter = null;
	private ArrayAdapter<Integer> _choiceSetAdapter = null;
	
	private static final int CHOICESETID_UNSET = -1;
	/**
	 * Latest choiceSetId, required to add it to the adapter when a successful
	 * CreateInteractionChoiceSetResponse comes.
	 */
	private int _latestChoiceSetId = CHOICESETID_UNSET;

	private int autoIncCorrId = 101;
	private int autoIncChoiceSetId = 1;
	private int autoIncChoiceSetIdCmdId = 1;
	private int itemcmdID = 1;
	private int submenucmdID = 1000;

	private ArrayAdapter<ButtonName> _buttonAdapter = null;
	private boolean[] isButtonSubscribed = null;
	
	private TcpDiscoverer mDiscoverer;

	/**
	 * In onCreate() specifies if it is the first time the activity is created
	 * during this app launch.
	 */
	private static boolean isFirstActivityRun = true;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
    	
    	_activity = this;

		setContentView(R.layout.main);
		_scroller = (ScrollView) findViewById(R.id.scrollConsole);

		((Button) findViewById(R.id.btnSendMessage)).setOnClickListener(this);
		((Button) findViewById(R.id.btnPlayPause)).setOnClickListener(this);
		((Button) findViewById(R.id.btnSendPMMessage)).setOnClickListener(this);
		((Button) findViewById(R.id.btnPMTests)).setOnClickListener(this);
		
		resetAdapters();
		
		_listview = (ListView) findViewById(R.id.messageList);
		_msgAdapter = new logAdapter(logTag, false, this, R.layout.row, _logMessages);
		_profileManagerTests = new ProfileManagerTests(_msgAdapter, this);
		
		_listview.setClickable(true);
		_listview.setAdapter(_msgAdapter);
		_listview.setTranscriptMode(ListView.TRANSCRIPT_MODE_ALWAYS_SCROLL);
		_listview.setOnItemClickListener(new OnItemClickListener() {
			public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
				Object listObj = parent.getItemAtPosition(position);
				if (listObj instanceof RPCMessage) {
					AlertDialog.Builder builder = new AlertDialog.Builder(SmartDeviceLinkTester.this);
					String rawJSON = "";
					
					Integer corrId = -1;
					if (listObj instanceof RPCRequest) {
						corrId = ((RPCRequest) listObj).getCorrelationID();
					} else if (listObj instanceof RPCResponse) {
						corrId = ((RPCResponse) listObj).getCorrelationID();
					}

					try {
						rawJSON = ((RPCMessage) listObj).serializeJSON().toString(2);
						builder.setTitle("Raw JSON" + (corrId != -1 ? " (Corr ID " + corrId + ")" : ""));
					} catch (Exception e) {
						try {rawJSON = ((RPCMessage) listObj).getFunctionName() + 
								" (" + ((RPCMessage) listObj).getMessageType() + ")";
						} catch (Exception e1) {rawJSON = "Undefined";}
					}
					builder.setMessage(rawJSON);
					builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int id) {
							dialog.cancel();
						}
					});
					AlertDialog ad = builder.create();
					ad.show();
				} else if (listObj instanceof String){
					AlertDialog.Builder builder = new AlertDialog.Builder(SmartDeviceLinkTester.this);
					builder.setMessage(listObj.toString());
					builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int id) {
							dialog.cancel();
						}
					});
					AlertDialog ad = builder.create();
					ad.show();
				}
			}
		});
		
		if (isFirstActivityRun) {
			propertiesUI();
		} else {
			showPropertiesInTitle();
			startSmartDeviceLinkProxy();
		}
		
		isFirstActivityRun = false;
	}

	/**
	 * Shows a dialog where the user can select connection features (protocol
	 * version, media flag, app name, language, HMI language, and transport
	 * settings). Starts the proxy after selecting.
	 */
	private void propertiesUI() {
		Context context = this;
		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.properties,
				(ViewGroup) findViewById(R.id.properties_Root));

		ArrayAdapter<Language> langAdapter = new ArrayAdapter<Language>(this,
				android.R.layout.simple_spinner_item, Language.values());
		langAdapter
				.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

		final CheckBox mediaCheckBox = (CheckBox) view
				.findViewById(R.id.properties_checkMedia);
		final EditText appNameEditText = (EditText) view
				.findViewById(R.id.properties_appName);
		final RadioGroup transportGroup = (RadioGroup) view
				.findViewById(R.id.properties_radioGroupTransport);
		final EditText ipAddressEditText = (EditText) view
				.findViewById(R.id.properties_ipAddr);
		final EditText tcpPortEditText = (EditText) view
				.findViewById(R.id.properties_tcpPort);
		final CheckBox autoReconnectCheckBox = (CheckBox) view
				.findViewById(R.id.properties_checkAutoReconnect);

		ipAddressEditText.setEnabled(false);
		tcpPortEditText.setEnabled(false);
		autoReconnectCheckBox.setEnabled(false);

		transportGroup
				.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
					@Override
					public void onCheckedChanged(RadioGroup group, int checkedId) {
						boolean transportOptionsEnabled = checkedId == R.id.properties_radioWiFi;
						ipAddressEditText.setEnabled(transportOptionsEnabled);
						tcpPortEditText.setEnabled(transportOptionsEnabled);
						autoReconnectCheckBox
								.setEnabled(transportOptionsEnabled);
					}
				});

		// display current configs
		final SharedPreferences prefs = getSharedPreferences(Const.PREFS_NAME,
				0);
		boolean isMedia = prefs.getBoolean(Const.PREFS_KEY_ISMEDIAAPP,
				Const.PREFS_DEFAULT_ISMEDIAAPP);
		String appName = prefs.getString(Const.PREFS_KEY_APPNAME,
				Const.PREFS_DEFAULT_APPNAME);
		int transportType = prefs.getInt(
				Const.Transport.PREFS_KEY_TRANSPORT_TYPE,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_TYPE);
		String ipAddress = prefs.getString(
				Const.Transport.PREFS_KEY_TRANSPORT_IP,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_IP);
		int tcpPort = prefs.getInt(Const.Transport.PREFS_KEY_TRANSPORT_PORT,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_PORT);
		boolean autoReconnect = prefs.getBoolean(
				Const.Transport.PREFS_KEY_TRANSPORT_RECONNECT,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_RECONNECT_DEFAULT);

		mediaCheckBox.setChecked(isMedia);
		appNameEditText.setText(appName);
		transportGroup
				.check(transportType == Const.Transport.KEY_TCP ? R.id.properties_radioWiFi
						: R.id.properties_radioBT);
		ipAddressEditText.setText(ipAddress);
		tcpPortEditText.setText(String.valueOf(tcpPort));
		autoReconnectCheckBox.setChecked(autoReconnect);

		new AlertDialog.Builder(context)
				.setTitle("Please select properties")
				.setCancelable(false)
				.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {

						String appName = appNameEditText.getText().toString();
						boolean isMedia = mediaCheckBox.isChecked();

                        int transportType = 0;
						switch(transportGroup.getCheckedRadioButtonId()){
						case R.id.properties_radioWiFi:
						    transportType = Const.Transport.KEY_TCP;
						    break;
						case R.id.properties_radioWiFiAuto:
						    transportType = Const.Transport.KEY_TCP_AUTO;
						    break;
						case R.id.properties_radioBT:
						    transportType = Const.Transport.KEY_BLUETOOTH;
						    break;
						}
						String ipAddress = ipAddressEditText.getText()
								.toString();
						int tcpPort = Integer.parseInt(tcpPortEditText
								.getText().toString());
						boolean autoReconnect = autoReconnectCheckBox
								.isChecked();

						// save the configs
						boolean success = prefs
								.edit()
								.putBoolean(Const.PREFS_KEY_ISMEDIAAPP, isMedia)
								.putString(Const.PREFS_KEY_APPNAME, appName)
								.putInt(Const.Transport.PREFS_KEY_TRANSPORT_TYPE,
										transportType == Const.Transport.KEY_TCP_AUTO ? Const.Transport.KEY_TCP : transportType)
								.putString(
										Const.Transport.PREFS_KEY_TRANSPORT_IP,
										ipAddress)
								.putInt(Const.Transport.PREFS_KEY_TRANSPORT_PORT,
										tcpPort)
								.putBoolean(
										Const.Transport.PREFS_KEY_TRANSPORT_RECONNECT,
										autoReconnect).commit();
						if (!success) {
							Log.w(logTag,
									"Can't save properties");
						}

						showPropertiesInTitle();
						if (transportType == Const.Transport.KEY_TCP_AUTO) {
						    mDiscoverer = new TcpDiscoverer(SmartDeviceLinkTester.this, SmartDeviceLinkTester.this);
						    mDiscoverer.performSearch();
						} else {
						    startSmartDeviceLinkProxy();
						}
					}
				}).setView(view).show();
	}

	/** Starts the SmartDeviceLink proxy at startup after selecting protocol features. */
	private void startSmartDeviceLinkProxy() {
		if (ProxyService.getInstance() == null) {
			Intent startIntent = new Intent(SmartDeviceLinkTester._activity, ProxyService.class);
			startService(startIntent);
		} else {
			ProxyService.getInstance().setCurrentActivity(SmartDeviceLinkTester._activity);
		}
	}

	/**
	 * Initializes/resets the adapters keeping created submenus, interaction
	 * choice set ids, etc.
	 */
	private void resetAdapters() {
		List<ButtonName> subscribableButtonNames = Arrays.asList(ButtonName.values()).
				subList(0, ButtonName.values().length - 1);
		isButtonSubscribed = new boolean[subscribableButtonNames.size()];
		_buttonAdapter = new ArrayAdapter<ButtonName>(this,
				android.R.layout.select_dialog_multichoice, subscribableButtonNames) {
			public View getView(int position, View convertView, ViewGroup parent) {
				CheckedTextView ret = (CheckedTextView) super.getView(position,
						convertView, parent);
				ret.setChecked(isButtonSubscribed[position]);
				return ret;
			}
		};

		_submenuAdapter = new ArrayAdapter<SmartDeviceLinkSubMenu>(this,
				android.R.layout.select_dialog_item);
		_submenuAdapter
				.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

		// Add top level menu with parent ID zero
		SmartDeviceLinkSubMenu sm = new SmartDeviceLinkSubMenu();
		sm.setName("Top Level Menu");
		sm.setSubMenuId(0);
		addSubMenuToList(sm);

		_commandAdapter = new ArrayAdapter<Integer>(this,
				android.R.layout.select_dialog_item);
		_commandAdapter
				.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

		_choiceSetAdapter = new ArrayAdapter<Integer>(this,
				android.R.layout.select_dialog_item);
		_choiceSetAdapter
				.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
	}

	/** Displays the current protocol properties in the activity's title. */
	private void showPropertiesInTitle() {
		final SharedPreferences prefs = getSharedPreferences(Const.PREFS_NAME,
				0);
		boolean isMedia = prefs.getBoolean(Const.PREFS_KEY_ISMEDIAAPP,
				Const.PREFS_DEFAULT_ISMEDIAAPP);
		String transportType = prefs.getInt(
				Const.Transport.PREFS_KEY_TRANSPORT_TYPE,
				Const.Transport.PREFS_DEFAULT_TRANSPORT_TYPE) == Const.Transport.KEY_TCP ? "WiFi"
				: "BT";
		setTitle(getResources().getString(R.string.app_name) + " ("
				+ (isMedia ? "" : "non-") + "media, "
				+ transportType + ")");
	}

	protected void onDestroy() {
		super.onDestroy();
		endSmartDeviceLinkProxyInstance();
		_activity = null;
		ProxyService service = ProxyService.getInstance();
		if (service != null) {
			service.setCurrentActivity(null);
		}
	}
	
	public Dialog onCreateDialog(int id) {
		Dialog dialog = null;
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		switch (id) {
			case 1:
				builder.setTitle("Raw JSON");
				builder.setMessage("This is the raw JSON message here");
				builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
						dialog.cancel();
					}
				});
				AlertDialog dialog1 = builder.create();
				dialog = dialog1;
				break;
			case 2:
				break;
			default:
				dialog = null;
		}
		return dialog;
	}
	private final int PROXY_START = 5;
	private final int XML_TEST = 7;
	private final int MNU_TOGGLE_CONSOLE = 9;
	private final int MNU_CLEAR = 10;
	private final int MNU_EXIT = 11;
	private final int MNU_TOGGLE_MEDIA = 12;
	private final int MNU_UNREGISTER = 14;

	
	/* Creates the menu items */
	public boolean onCreateOptionsMenu(Menu menu) {
		boolean result = super.onCreateOptionsMenu(menu);
		if (result) {
			menu.add(0, PROXY_START, 0, "Proxy Start");
			menu.add(0, MNU_TOGGLE_CONSOLE, 0, "Toggle Console");
			menu.add(0, MNU_CLEAR, 0, "Clear Messages");
			menu.add(0, MNU_EXIT, 0, "Exit");
			menu.add(0, MNU_UNREGISTER, 0, "Unregister");
			menu.add(0, XML_TEST, 0, "XML Test");
			return true;
		} else {
			return false;
		}
	}

	private boolean getIsMedia() {
		return getSharedPreferences(Const.PREFS_NAME, 0).getBoolean(
				Const.PREFS_KEY_ISMEDIAAPP, Const.PREFS_DEFAULT_ISMEDIAAPP);
	}

	/* Handles item selections */
	public boolean onOptionsItemSelected(MenuItem item) {

		switch (item.getItemId()) {
        case PROXY_START:
	        BluetoothAdapter mBtAdapter = BluetoothAdapter.getDefaultAdapter();
	        if (!mBtAdapter.isEnabled()) mBtAdapter.enable();
	        
	        if (ProxyService.getInstance() == null) {
                Intent startIntent = new Intent(this, ProxyService.class);
                startService(startIntent);
	        } else {
                ProxyService.getInstance().setCurrentActivity(this);
	        }
	        
	        if (ProxyService.getInstance().getProxyInstance() != null) {
                try {
                        ProxyService.getInstance().getProxyInstance().resetProxy();
                } catch (SmartDeviceLinkException e) {}
	        }
	        
	        if (!mBtAdapter.isDiscovering()) {
                Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
                discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
                startActivity(discoverableIntent);
	        }
			return true;

		case XML_TEST:
			if (_testerMain != null) {
				_testerMain.restart();
				Toast.makeText(getApplicationContext(), "start your engines", Toast.LENGTH_SHORT).show();
			}else {
				ProxyService.getInstance().startModuleTest();
				_testerMain.restart();
				Toast.makeText(getApplicationContext(), "Start the app on SmartDeviceLink first", Toast.LENGTH_LONG).show();
			}
			break;
		case MNU_EXIT:
			exitApp();
			break;
		case MNU_TOGGLE_CONSOLE:
			if (_scroller.getVisibility() == ScrollView.VISIBLE) {
				_scroller.setVisibility(ScrollView.GONE);
				_listview.setVisibility(ListView.VISIBLE);
			} else {
				_scroller.setVisibility(ScrollView.VISIBLE);
				_listview.setVisibility(ListView.GONE);
			}
			return true;
		case MNU_CLEAR:
			_msgAdapter.clear();
			return true;
		case MNU_TOGGLE_MEDIA:
			SharedPreferences settings = getSharedPreferences(Const.PREFS_NAME, 0);
			boolean isMediaApp = settings.getBoolean(Const.PREFS_KEY_ISMEDIAAPP, Const.PREFS_DEFAULT_ISMEDIAAPP);
			SharedPreferences.Editor editor = settings.edit();
			editor.putBoolean(Const.PREFS_KEY_ISMEDIAAPP, !isMediaApp);
			editor.commit();
			return true;
		case MNU_UNREGISTER:
			endSmartDeviceLinkProxyInstance();
			startSmartDeviceLinkProxy();
			return true;
		}
		
		return false;
	}
	
	/** Closes the activity and stops the proxy service. */
	private void exitApp() {
		stopService(new Intent(this, ProxyService.class));
		finish();
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				android.os.Process.killProcess(android.os.Process.myPid());
			}
		}, 1000);
	}

	public void onClick(View v) {
		if (v == findViewById(R.id.btnSendMessage)) {
			final ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.select_dialog_item);
			adapter.add(Names.Alert);
			adapter.add(Names.Speak);
			adapter.add(Names.Show);
			adapter.add(ButtonSubscriptions);
			adapter.add(Names.AddCommand);
			adapter.add(Names.DeleteCommand);
			adapter.add(Names.AddSubMenu);
			adapter.add(Names.DeleteSubMenu);
			adapter.add(Names.SetGlobalProperties);
			adapter.add(Names.ResetGlobalProperties);
			adapter.add(Names.SetMediaClockTimer);
			adapter.add(Names.CreateInteractionChoiceSet);
			adapter.add(Names.DeleteInteractionChoiceSet);
			adapter.add(Names.PerformInteraction);
			adapter.add(Names.EncodedSyncPData);
			
			new AlertDialog.Builder(this)  
		       .setTitle("Pick a Function")
		       .setAdapter(adapter, new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						if(adapter.getItem(which) == Names.Alert){
							AlertDialog.Builder builder;
							AlertDialog dlg;

							final Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.alert, null);
							final EditText txtSpeak = (EditText) layout.findViewById(R.id.txtSpeak);
							final EditText txtAlertField1 = (EditText) layout.findViewById(R.id.txtAlertField1);
							final EditText txtAlertField2 = (EditText) layout.findViewById(R.id.txtAlertField2);
							final EditText txtDuration = (EditText) layout.findViewById(R.id.txtDuration);
							final CheckBox chkPlayTone = (CheckBox) layout.findViewById(R.id.chkPlayTone);
							
							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									String toSpeak = txtSpeak.getText().toString();
									try {
										Alert msg = new Alert();
										msg.setCorrelationID(autoIncCorrId++);
										msg.setAlertText1(txtAlertField1.getText().toString());
										msg.setAlertText2(txtAlertField2.getText().toString());
										msg.setDuration(Integer.parseInt(txtDuration.getText().toString()));
										msg.setPlayTone(chkPlayTone.isChecked());
										if (toSpeak.length() > 0) {
											Vector<TTSChunk> ttsChunks = TTSChunkFactory.createSimpleTTSChunks(toSpeak);
											msg.setTtsChunks(ttsChunks);
										}
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							dlg = builder.create();
							dlg.show();	
						} else if (adapter.getItem(which) == Names.Speak) {
							//something
							AlertDialog.Builder builder;
							AlertDialog dlg;

							Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.speak, null);
							final EditText txtSpeakText1 = (EditText) layout.findViewById(R.id.txtSpeakText1);
							final EditText txtSpeakText2 = (EditText) layout.findViewById(R.id.txtSpeakText2);
							final EditText txtSpeakText3 = (EditText) layout.findViewById(R.id.txtSpeakText3);
							final EditText txtSpeakText4 = (EditText) layout.findViewById(R.id.txtSpeakText4);
							
							final Spinner spnSpeakType1 = (Spinner) layout.findViewById(R.id.spnSpeakType1);
							final Spinner spnSpeakType2 = (Spinner) layout.findViewById(R.id.spnSpeakType2);
							final Spinner spnSpeakType3 = (Spinner) layout.findViewById(R.id.spnSpeakType3);
							final Spinner spnSpeakType4 = (Spinner) layout.findViewById(R.id.spnSpeakType4);
							
							ArrayAdapter<SpeechCapabilities> speechSpinnerAdapter = new ArrayAdapter<SpeechCapabilities>(adapter.getContext(), android.R.layout.simple_spinner_item, SpeechCapabilities.values()); 
							spnSpeakType1.setAdapter(speechSpinnerAdapter);
							spnSpeakType2.setAdapter(speechSpinnerAdapter);
							spnSpeakType2.setSelection(3);
							spnSpeakType3.setAdapter(speechSpinnerAdapter);
							spnSpeakType4.setAdapter(speechSpinnerAdapter);
							spnSpeakType4.setSelection(1);
							spnSpeakType4.setEnabled(false);
							
							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									Speak msg = new Speak();
									msg.setCorrelationID(autoIncCorrId++);
									String speak1 = txtSpeakText1.getText().toString();
									String speak2 = txtSpeakText2.getText().toString();
									String speak3 = txtSpeakText3.getText().toString();
									String speak4 = txtSpeakText4.getText().toString();
									Vector<TTSChunk> chunks = new Vector<TTSChunk>();

									if (speak1.length() > 0) {
										chunks.add(TTSChunkFactory.createChunk((SpeechCapabilities)spnSpeakType1.getSelectedItem(), speak1));
										
									}
									if (speak2.length() > 0) {
										chunks.add(TTSChunkFactory.createChunk((SpeechCapabilities)spnSpeakType2.getSelectedItem(), speak2));
										
									}
									if (speak3.length() > 0) {
										chunks.add(TTSChunkFactory.createChunk((SpeechCapabilities)spnSpeakType3.getSelectedItem(), speak3));
										
									}
									if (speak4.length() > 0) {
										chunks.add(TTSChunkFactory.createChunk(SpeechCapabilities.SAPI_PHONEMES, speak4));
										
									}
									msg.setTtsChunks(chunks);
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.Show) {
							//something
							AlertDialog.Builder builder;
							AlertDialog dlg;

							final Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.show, null);
							final EditText txtShowField1 = (EditText) layout.findViewById(R.id.txtShowField1);
							final EditText txtShowField2 = (EditText) layout.findViewById(R.id.txtShowField2);
							final EditText statusBar = (EditText) layout.findViewById(R.id.txtStatusBar);
							final EditText mediaClock = (EditText) layout.findViewById(R.id.txtMediaClock);
							final EditText mediaTrack = (EditText) layout.findViewById(R.id.txtMediaTrack);
							
							if (!getIsMedia()) {
								int visibility = android.view.View.GONE;
								mediaClock.setVisibility(visibility);
								mediaTrack.setVisibility(visibility);
								layout.findViewById(R.id.lblMediaTrack).setVisibility(visibility);
								layout.findViewById(R.id.lblMediaClock).setVisibility(visibility);
							}

							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									try {
										Show msg = new Show();
										msg.setCorrelationID(autoIncCorrId++);
										msg.setMainField1(txtShowField1.getText().toString());
										msg.setMainField2(txtShowField2.getText().toString());
										msg.setStatusBar(statusBar.getText().toString());
										if (getIsMedia()) {
											msg.setMediaClock(mediaClock.getText().toString());
											msg.setMediaTrack(mediaTrack.getText().toString());
										}
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == ButtonSubscriptions) {
							//something
							AlertDialog.Builder builder = new AlertDialog.Builder(adapter.getContext());
							builder.setAdapter(_buttonAdapter, new DialogInterface.OnClickListener() {

								public void onClick(DialogInterface dialog, int which) {
								boolean needToSubscribe = !isButtonSubscribed[which];
									try {
										ButtonName buttonName = ButtonName.values()[which];
										int corrId = autoIncCorrId++;
										if (needToSubscribe) {
											SubscribeButton msg = new SubscribeButton();
											msg.setCorrelationID(corrId);
											msg.setButtonName(buttonName);
											_msgAdapter.logMessage(msg, true);
											ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
										} else {
											UnsubscribeButton msg = new UnsubscribeButton();
											msg.setCorrelationID(corrId);
											msg.setButtonName(buttonName);
											_msgAdapter.logMessage(msg, true);
											ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
										}
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
									isButtonSubscribed[which] = !isButtonSubscribed[which];
								}
							});
							AlertDialog dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.AddCommand) {
							//something
							AlertDialog.Builder builder;
							AlertDialog addCommandDialog;

							Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.addcommand,
									(ViewGroup) findViewById(R.id.itemRoot));

							final EditText er = (EditText) layout.findViewById(R.id.command);
							final EditText editVrSynonym = (EditText) layout.findViewById(R.id.command2);
							final Spinner s = (Spinner) layout.findViewById(R.id.availableSubmenus);
							s.setAdapter(_submenuAdapter);
							
							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									AddCommand msg = new AddCommand();
									msg.setCorrelationID(autoIncCorrId++);
									String itemText = er.getText().toString();
									SmartDeviceLinkSubMenu sm = new SmartDeviceLinkSubMenu();
									sm = (SmartDeviceLinkSubMenu) s.getSelectedItem();
									MenuParams menuParams = new MenuParams();
									menuParams.setMenuName(itemText);
									menuParams.setPosition(0);
									menuParams.setParentID(sm.getSubMenuId());
									msg.setMenuParams(menuParams);
									
									String vrSynonym = editVrSynonym.getText().toString();
									if (vrSynonym.length() > 0) {
										Vector<String> vrCommands = new Vector<String>();
										vrCommands.add(vrSynonym);
										msg.setVrCommands(vrCommands);
									}
									
									int cmdID = itemcmdID++;
									msg.setCmdID(cmdID);
									
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
									_commandAdapter.add(cmdID);
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							addCommandDialog = builder.create();
							addCommandDialog.show();
						} else if (adapter.getItem(which) == Names.DeleteCommand) {
							//something
							AlertDialog.Builder builder = new AlertDialog.Builder(adapter.getContext());
							builder.setAdapter(_commandAdapter, new DialogInterface.OnClickListener() {

								public void onClick(DialogInterface dialog, int which) {
									DeleteCommand msg = new DeleteCommand();
									msg.setCorrelationID(autoIncCorrId++);
									int cmdID = _commandAdapter.getItem(which);
									msg.setCmdID(cmdID);
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
									_commandAdapter.remove(cmdID);
								}
							});
							AlertDialog dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.AddSubMenu) {
							//something
							AlertDialog.Builder builder;
							AlertDialog addSubMenuDialog;

							Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.addsubmenu,
									(ViewGroup) findViewById(R.id.submenu_Root));

							final EditText subMenu = (EditText) layout.findViewById(R.id.submenu_item);

							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									AddSubMenu msg = new AddSubMenu();
									msg.setCorrelationID(autoIncCorrId++);
									SmartDeviceLinkSubMenu sm = new SmartDeviceLinkSubMenu();
									sm.setName(subMenu.getText().toString());
									sm.setSubMenuId(submenucmdID++);
									addSubMenuToList(sm);
									msg.setMenuID(sm.getSubMenuId());
									msg.setMenuName(sm.getName());
									msg.setPosition(null);
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							addSubMenuDialog = builder.create();
							addSubMenuDialog.show();
						} else if (adapter.getItem(which) == Names.DeleteSubMenu) {
							//something
							AlertDialog.Builder builder = new AlertDialog.Builder(adapter.getContext());
							builder.setAdapter(_submenuAdapter, new DialogInterface.OnClickListener() {

								public void onClick(DialogInterface dialog, int which) {
									SmartDeviceLinkSubMenu menu = _submenuAdapter.getItem(which);
									if (menu.getSubMenuId() != 0) {
										DeleteSubMenu msg = new DeleteSubMenu();
										msg.setCorrelationID(autoIncCorrId++);
										msg.setMenuID(menu.getSubMenuId());
										try {
											_msgAdapter.logMessage(msg, true);
											ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
										} catch (SmartDeviceLinkException e) {
											_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
										}
	
										_submenuAdapter.remove(menu);
									} else {
										Toast.makeText(getApplicationContext(),
												"Sorry, can't delete top-level menu",
												Toast.LENGTH_LONG).show();
									}
								}
							});
							AlertDialog dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.SetGlobalProperties) {
							sendSetGlobalProperties();
						} else if (adapter.getItem(which) == Names.ResetGlobalProperties) {
							sendResetGlobalProperties();
						} else if (adapter.getItem(which) == Names.SetMediaClockTimer) {
							//something
							AlertDialog.Builder builder;
							AlertDialog dlg;

							Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.setmediaclock, null);
							final EditText txtHours = (EditText) layout.findViewById(R.id.txtHours);
							final EditText txtMinutes = (EditText) layout.findViewById(R.id.txtMinutes);
							final EditText txtSeconds = (EditText) layout.findViewById(R.id.txtSeconds);
							final Spinner spnUpdateMode = (Spinner) layout.findViewById(R.id.spnUpdateMode);
							ArrayAdapter<UpdateMode> spinnerAdapter = new ArrayAdapter<UpdateMode>(adapter.getContext(),
									android.R.layout.simple_spinner_item, UpdateMode.values());
							spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
							spnUpdateMode.setAdapter(spinnerAdapter);
							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									SetMediaClockTimer msg = new SetMediaClockTimer();
									msg.setCorrelationID(autoIncCorrId++);
									UpdateMode updateMode =  (UpdateMode)spnUpdateMode.getSelectedItem();
									msg.setUpdateMode(updateMode);
									try {
										Integer hours = Integer.parseInt(txtHours.getText().toString());
										Integer minutes = Integer.parseInt(txtMinutes.getText().toString());
										Integer seconds = Integer.parseInt(txtSeconds.getText().toString());
										StartTime startTime = new StartTime();
										startTime.setHours(hours);
										startTime.setMinutes(minutes);
										startTime.setSeconds(seconds);
										msg.setStartTime(startTime);
									} catch (NumberFormatException e) {
										// skip setting start time if parsing failed
									}
									
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.CreateInteractionChoiceSet) {
							//something
							AlertDialog.Builder builder;
							AlertDialog createCommandSet;

							Context mContext = adapter.getContext();
							LayoutInflater inflater = (LayoutInflater) mContext
									.getSystemService(LAYOUT_INFLATER_SERVICE);
							View layout = inflater.inflate(R.layout.createinteractionchoices,
									(ViewGroup) findViewById(R.id.createcommands_Root));

							final EditText command1 = (EditText) layout.findViewById(R.id.createcommands_command1);
							final EditText command2 = (EditText) layout.findViewById(R.id.createcommands_command2);
							final EditText command3 = (EditText) layout.findViewById(R.id.createcommands_command3);
							final EditText vr1 = (EditText) layout.findViewById(R.id.createcommands_vr1);
							final EditText vr2 = (EditText) layout.findViewById(R.id.createcommands_vr2);
							final EditText vr3 = (EditText) layout.findViewById(R.id.createcommands_vr3);
							final CheckBox choice1 = (CheckBox) layout.findViewById(R.id.createcommands_choice1);
							final CheckBox choice2 = (CheckBox) layout.findViewById(R.id.createcommands_choice2);
							final CheckBox choice3 = (CheckBox) layout.findViewById(R.id.createcommands_choice3);

							builder = new AlertDialog.Builder(mContext);
							builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									Vector<Choice> commands = new Vector<Choice>();
									
									if (choice1.isChecked()) {
										Choice one = new Choice();
										one.setChoiceID(autoIncChoiceSetIdCmdId++);
										one.setMenuName(command1.getText().toString());
										one.setVrCommands(new Vector<String>(Arrays.asList(new String[] { command1.getText().toString(),
												vr1.getText().toString() })));
										commands.add(one);
									}
									
									if (choice2.isChecked()) {
										Choice two = new Choice();
										two.setChoiceID(autoIncChoiceSetIdCmdId++);
										two.setMenuName(command2.getText().toString());
										two.setVrCommands(new Vector<String>(Arrays.asList(new String[] { command2.getText().toString(),
												vr2.getText().toString() })));
										commands.add(two);
									}
									
									if (choice3.isChecked()) {
										Choice three = new Choice();
										three.setChoiceID(autoIncChoiceSetIdCmdId++);
										three.setMenuName(command3.getText().toString());
										three.setVrCommands(new Vector<String>(Arrays.asList(new String[] { command3.getText().toString(),
												vr3.getText().toString() })));
										commands.add(three);
									}
									
									if (!commands.isEmpty()) {
										CreateInteractionChoiceSet msg = new CreateInteractionChoiceSet();
										msg.setCorrelationID(autoIncCorrId++);
										int choiceSetID = autoIncChoiceSetId++;
										msg.setInteractionChoiceSetID(choiceSetID);
										msg.setChoiceSet(commands);
										try {
											_msgAdapter.logMessage(msg, true);
											ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
											if (_latestChoiceSetId != CHOICESETID_UNSET) {
												Log.w(logTag, "Latest choiceSetId should be unset, but equals to " + _latestChoiceSetId);
											}
											_latestChoiceSetId = choiceSetID;
										} catch (SmartDeviceLinkException e) {
											_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
										}
									} else {
										Toast.makeText(getApplicationContext(), "No commands to set", Toast.LENGTH_SHORT).show();
									}
								}
							});
							builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
								}
							});
							builder.setView(layout);
							createCommandSet = builder.create();
							createCommandSet.show();
						} else if (adapter.getItem(which) == Names.DeleteInteractionChoiceSet) {
							//something
							AlertDialog.Builder builder = new AlertDialog.Builder(adapter.getContext());
							builder.setAdapter(_choiceSetAdapter, new DialogInterface.OnClickListener() {

								public void onClick(DialogInterface dialog, int which) {
									DeleteInteractionChoiceSet msg = new DeleteInteractionChoiceSet();
									msg.setCorrelationID(autoIncCorrId++);
									int commandSetID = _choiceSetAdapter.getItem(which);
									msg.setInteractionChoiceSetID(commandSetID);
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}

									_choiceSetAdapter.remove(commandSetID);
								}
							});
							AlertDialog dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.PerformInteraction) {
							//something
							AlertDialog.Builder builder = new AlertDialog.Builder(adapter.getContext());
							builder.setAdapter(_choiceSetAdapter, new DialogInterface.OnClickListener() {

								public void onClick(DialogInterface dialog, int which) {
									PerformInteraction msg = new PerformInteraction();
									msg.setCorrelationID(autoIncCorrId++);
									Vector<Integer> interactionChoiceSetIDs = new Vector<Integer>();
									interactionChoiceSetIDs.add(_choiceSetAdapter.getItem(which));
									Vector<TTSChunk> initChunks = TTSChunkFactory
											.createSimpleTTSChunks("Pick a command");
									Vector<TTSChunk> helpChunks = TTSChunkFactory
											.createSimpleTTSChunks("help me, I'm melting");
									Vector<TTSChunk> timeoutChunks = TTSChunkFactory
											.createSimpleTTSChunks("hurry it up");
									msg.setInitialPrompt(initChunks);
									msg.setInitialText("Pick number:");
									msg.setInteractionChoiceSetIDList(interactionChoiceSetIDs);
									msg.setInteractionMode(InteractionMode.BOTH);
									msg.setTimeout(10000);
									msg.setHelpPrompt(helpChunks);
									msg.setTimeoutPrompt(timeoutChunks);
									try {
										_msgAdapter.logMessage(msg, true);
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								}
							});
							AlertDialog dlg = builder.create();
							dlg.show();
						} else if (adapter.getItem(which) == Names.EncodedSyncPData) {
							//EncodedSyncPData
							EncodedSyncPData msg = new EncodedSyncPData();
							Vector<String> SmartDeviceLinkPData = new Vector<String>();
							SmartDeviceLinkPData.add("AAM4AAkAAAAAAAAAAAA=");
							msg.setData(SmartDeviceLinkPData);
							msg.setCorrelationID(autoIncCorrId++);
							
							_msgAdapter.logMessage(msg, true);
							
							try {
								ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
							} catch (SmartDeviceLinkException e) {
								_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
							}
						}
					}

					private void sendSetGlobalProperties() {
						AlertDialog.Builder builder;

						Context mContext = adapter.getContext();
						LayoutInflater inflater = (LayoutInflater) mContext
								.getSystemService(LAYOUT_INFLATER_SERVICE);
						View layout = inflater.inflate(R.layout.setglobalproperties,
								(ViewGroup) findViewById(R.id.setglobalproperties_Root));

						final EditText helpPrompt = (EditText) layout.findViewById(R.id.setglobalproperties_helpPrompt);
						final EditText timeoutPrompt = (EditText) layout.findViewById(R.id.setglobalproperties_timeoutPrompt);
						final CheckBox choiceHelpPrompt = (CheckBox) layout.findViewById(R.id.setglobalproperties_choiceHelpPrompt);
						final CheckBox choiceTimeoutPrompt = (CheckBox) layout.findViewById(R.id.setglobalproperties_choiceTimeoutPrompt);

						builder = new AlertDialog.Builder(mContext);
						builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int id) {
								SetGlobalProperties msg = new SetGlobalProperties();
								int numberOfChoices = 0;
								
								if (choiceHelpPrompt.isChecked()) {
									Vector<TTSChunk> help = new Vector<TTSChunk>();
									help.add(TTSChunkFactory.createChunk(SpeechCapabilities.TEXT, helpPrompt.getText().toString()));
									msg.setHelpPrompt(help);
									++numberOfChoices;
								}

								if (choiceTimeoutPrompt.isChecked()) {
									Vector<TTSChunk> timeout = new Vector<TTSChunk>();
									timeout.add(TTSChunkFactory.createChunk(SpeechCapabilities.TEXT, timeoutPrompt.getText().toString()));
									msg.setTimeoutPrompt(timeout);
									++numberOfChoices;
								}
								
								if (numberOfChoices > 0) {
									msg.setCorrelationID(autoIncCorrId++);
									_msgAdapter.logMessage(msg, true);
									try {
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								} else {
									Toast.makeText(getApplicationContext(), "No items selected", Toast.LENGTH_LONG).show();
								}
							}
						});
						builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int id) {
								dialog.cancel();
							}
						});
						builder.setView(layout);
						builder.create().show();
					}

					private void sendResetGlobalProperties() {
						AlertDialog.Builder builder;

						Context mContext = adapter.getContext();
						LayoutInflater inflater = (LayoutInflater) mContext
								.getSystemService(LAYOUT_INFLATER_SERVICE);
						View layout = inflater.inflate(R.layout.resetglobalproperties,
								(ViewGroup) findViewById(R.id.resetglobalproperties_Root));

						final CheckBox choiceHelpPrompt = (CheckBox) layout.findViewById(R.id.resetglobalproperties_choiceHelpPrompt);
						final CheckBox choiceTimeoutPrompt = (CheckBox) layout.findViewById(R.id.resetglobalproperties_choiceTimeoutPrompt);

						builder = new AlertDialog.Builder(mContext);
						builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int id) {
								ResetGlobalProperties msg = new ResetGlobalProperties();
								Vector<GlobalProperty> properties = new Vector<GlobalProperty>();
								
								if (choiceHelpPrompt.isChecked()) {
									properties.add(GlobalProperty.HELPPROMPT);
								}

								if (choiceTimeoutPrompt.isChecked()) {
									properties.add(GlobalProperty.TIMEOUTPROMPT);
								}

								if (!properties.isEmpty()) {
									msg.setProperties(properties);
									msg.setCorrelationID(autoIncCorrId++);
									_msgAdapter.logMessage(msg, true);
									try {
										ProxyService.getInstance().getProxyInstance().sendRPCRequest(msg);
									} catch (SmartDeviceLinkException e) {
										_msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
									}
								} else {
									Toast.makeText(getApplicationContext(), "No items selected", Toast.LENGTH_LONG).show();
								}
							}
						});
						builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int id) {
								dialog.cancel();
							}
						});
						builder.setView(layout);
						builder.create().show();
					}
				})
		       .setNegativeButton("Close", null)
		       .show();			
		} else if (v == findViewById(R.id.btnPlayPause)) {
			ProxyService.getInstance().playPauseAnnoyingRepetitiveAudio();
		} else if (v == findViewById(R.id.btnSendPMMessage)) {
            showProfileManagerControls();
		} else if (v == findViewById(R.id.btnPMTests)) {
		    _profileManagerTests.runProfileManagerTests();
		}
		
	}

	public void addSubMenuToList(final SmartDeviceLinkSubMenu sm) {
		runOnUiThread(new Runnable() {
			public void run() {
				_submenuAdapter.add(sm);
			}
		});
	}
	
	//upon onDestroy(), dispose current proxy and create a new one to enable auto-start
	//call resetProxy() to do so
	public void endSmartDeviceLinkProxyInstance() {	
		ProxyService serviceInstance = ProxyService.getInstance();
		if (serviceInstance != null){
			SmartDeviceLinkProxyALM proxyInstance = serviceInstance.getProxyInstance();
			//if proxy exists, reset it
			if(proxyInstance != null){
				if (proxyInstance.getCurrentTransportType() == TransportType.BLUETOOTH) {
					serviceInstance.reset();
				} else {
					Log.e(logTag, "endSmartDeviceLinkProxyInstance. No reset required if transport is TCP");
				}
			//if proxy == null create proxy
			} else {
				serviceInstance.startProxy();
			}
		}
	}
    
    public static SmartDeviceLinkTester getInstance() {
		return _activity;
	}
    
    public static logAdapter getMessageAdapter() {
		return _msgAdapter;
	}
    
	public void setTesterMain(ModuleTest _instance) {
		this._testerMain = _instance;
	}

	@Override
	public void onBackPressed() {
		moveTaskToBack(true);
	}
	
	@Override
	public void onPause() {
		super.onPause();
	}
	
	/**
	 * Called when a CreateChoiceSetResponse comes. If successful, add it to the
	 * adapter. In any case, remove the key from the map.
	 */
	public void onCreateChoiceSetResponse(boolean success) {
		if (_latestChoiceSetId != CHOICESETID_UNSET) {
			if (success) {
				_choiceSetAdapter.add(_latestChoiceSetId);
			}
			_latestChoiceSetId = CHOICESETID_UNSET;
		} else {
			Log.w(logTag, "Latest choiceSetId is unset");
		}
	}

	/** Called when a connection to a SmartDeviceLink device has been closed. */
	public void onProxyClosed() {
		resetAdapters();
		_msgAdapter.logMessage("Disconnected", true);
	}
	
	/**
	 * Called when the app is acivated from HMI for the first time. ProxyService
	 * automatically subscribes to buttons, so we reflect that in the
	 * subscription list.
	 */
	public void buttonsSubscribed(Vector<ButtonName> buttons) {
		List<ButtonName> buttonNames = Arrays.asList(ButtonName.values());
		for (ButtonName buttonName : buttons) {
			isButtonSubscribed[buttonNames.indexOf(buttonName)] = true;
		}
	}

    @Override
    public void onUserSelectedItem(String ip, String port) {
        mDiscoverer = null;
        getSharedPreferences(Const.PREFS_NAME, 0) 
        .edit()
        .putString(Const.Transport.PREFS_KEY_TRANSPORT_IP, ip)
        .putInt(Const.Transport.PREFS_KEY_TRANSPORT_PORT, Integer.parseInt(port))
        .commit();
        startSmartDeviceLinkProxy();
    }

    @Override
    public void onUserDismissedDialog() {
        mDiscoverer.performSearch();        
    }

    @Override
    public void onDiscovererFoundNothing() {
        mDiscoverer.performSearch();        
    }

    @Override
    public String getDismissDialogButtonName() {
        return "Continue search";
    }
    
    private void showProfileManagerControls() {
        new AlertDialog.Builder(this)
            .setTitle("Pick a Function")
            .setAdapter(getAdapterWithProfManCommands(), mProfileManagerControlsListener)
            .setNegativeButton("Close", null)
            .show();
    }

    private final static String[] mProfileManagerSingleTestCommands = { Names.addProfile, Names.removeProfile,
            Names.loadProfile, Names.unloadProfile, Names.sendAppToProfileMessage, Names.appStateChanged };
    private final static Map<String, Integer> mProfileManaterTestCommandsIndexes = new HashMap<String, Integer>();
    static {
        for (int i = 0; i < mProfileManagerSingleTestCommands.length; i++) {
            mProfileManaterTestCommandsIndexes.put(mProfileManagerSingleTestCommands[i], i);
        }
    }

    private ArrayAdapter<String> getAdapterWithProfManCommands() {
        final ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.select_dialog_item,
                mProfileManagerSingleTestCommands);
        return adapter;
    }
    
    private DialogInterface.OnClickListener mProfileManagerControlsListener = new DialogInterface.OnClickListener() {
        public void onClick(DialogInterface dialog, final int which) {
            AlertDialog.Builder builder;
            AlertDialog dlg;
            final Context context = SmartDeviceLinkTester.this;
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(LAYOUT_INFLATER_SERVICE);
            View layout = inflater.inflate(R.layout.pm_general, null);
            final EditText txtProfileName = (EditText) layout.findViewById(R.id.txtedProfileName);
            final EditText txtMessage = (EditText) layout.findViewById(R.id.txtPMMessage);
            final Spinner spnState = (Spinner) layout.findViewById(R.id.spnProfileState);
            ArrayAdapter<MobileAppState> spinnerAdapter = new ArrayAdapter<MobileAppState>(context,
                    android.R.layout.simple_spinner_item, MobileAppState.values());
            spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            spnState.setAdapter(spinnerAdapter);

            if (which == mProfileManaterTestCommandsIndexes.get(Names.appStateChanged)) {
                spnState.setVisibility(View.VISIBLE);
            } else if (which == mProfileManaterTestCommandsIndexes.get(Names.sendAppToProfileMessage)) {
                txtMessage.setVisibility(View.VISIBLE);
            }

            builder = new AlertDialog.Builder(context);
            builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    try {
                        RPCRequest msg = null;
                        String profileName = txtProfileName.getText().toString();
                        if (which == mProfileManaterTestCommandsIndexes.get(Names.addProfile)) {
                            // TODO this should be done in an AsyncTask for real profiles
                            byte[] profileData = loadAssetsFile("lib" + profileName + ".so");
                            if (profileData != null) {
                                autoIncCorrId = ProxyService.getProxyInstance().addProfile(profileName, profileData, autoIncCorrId);
                                autoIncCorrId++;
                            }
                        } else if (which == mProfileManaterTestCommandsIndexes.get(Names.removeProfile)) {
                            msg = RPCRequestFactory.buildRemoveProfile(profileName, autoIncCorrId++);
                        } else if (which == mProfileManaterTestCommandsIndexes.get(Names.loadProfile)) {
                            msg = RPCRequestFactory.buildLoadProfile(profileName, autoIncCorrId++);
                        } else if (which == mProfileManaterTestCommandsIndexes.get(Names.unloadProfile)) {
                            msg = RPCRequestFactory.buildUnloadProfile(profileName, autoIncCorrId++);
                        } else if (which == mProfileManaterTestCommandsIndexes.get(Names.appStateChanged)) {
                            msg = RPCRequestFactory.buildAppStateChanged(profileName,
                                    (MobileAppState) spnState.getSelectedItem(), autoIncCorrId++);
                        } else if (which == mProfileManaterTestCommandsIndexes.get(Names.sendAppToProfileMessage)) {
                            msg = RPCRequestFactory.buildSendAppToProfileMessage(profileName, txtMessage.getText()
                                    .toString().getBytes(), autoIncCorrId++);
                        }

                        if (msg != null) {
                            _msgAdapter.logMessage(msg, true);
                            ProxyService.getProxyInstance().sendRPCRequest(msg);
                        }

                    } catch (SmartDeviceLinkException e) {
                        _msgAdapter.logMessage("Error sending message: " + e, Log.ERROR, e);
                    }
                }
            });
            builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    dialog.cancel();
                }
            });
            builder.setView(layout);
            dlg = builder.create();
            dlg.show();
        }
    };
    
    public void handlePMMessage(RPCMessage message) {
        _profileManagerTests.handleMessage(message);
    }

    public byte[] loadAssetsFile(String fileName) {
        try {
            InputStream stream = getAssets().open(fileName);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            return buffer;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}

