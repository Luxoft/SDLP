//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.ButtonEventMode;
import com.smartdevicelink.proxy.rpc.enums.ButtonName;
import com.smartdevicelink.util.DebugTool;

public class OnButtonEvent extends RPCNotification {

    public OnButtonEvent() {
        super("OnButtonEvent");
    }
    public OnButtonEvent(Hashtable hash) {
        super(hash);
    }
    public ButtonName getButtonName() {
        Object obj = parameters.get(Names.buttonName);
        if (obj instanceof ButtonName) {
            return (ButtonName) obj;
        } else if (obj instanceof String) {
            ButtonName theCode = null;
            try {
                theCode = ButtonName.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.buttonName, e);
            }
            return theCode;
        }
        return null;
    }
    public void setButtonName( ButtonName buttonName ) {
        if (buttonName != null) {
            parameters.put(Names.buttonName, buttonName );
        }
    }
    public ButtonEventMode getButtonEventMode() {
        Object obj = parameters.get(Names.buttonEventMode);
        if (obj instanceof ButtonEventMode) {
            return (ButtonEventMode) obj;
        } else if (obj instanceof String) {
            ButtonEventMode theCode = null;
            try {
                theCode = ButtonEventMode.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.buttonEventMode, e);
            }
            return theCode;
        }
        return null;
    }
    public void setButtonEventMode( ButtonEventMode buttonEventMode ) {
        if (buttonEventMode != null) {
            parameters.put(Names.buttonEventMode, buttonEventMode );
        }
    }
}
