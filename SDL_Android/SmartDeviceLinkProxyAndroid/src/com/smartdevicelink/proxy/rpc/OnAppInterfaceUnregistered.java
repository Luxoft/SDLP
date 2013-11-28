//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.AppInterfaceUnregisteredReason;
import com.smartdevicelink.util.DebugTool;

public class OnAppInterfaceUnregistered extends RPCNotification {

    public OnAppInterfaceUnregistered() {
        super("OnAppInterfaceUnregistered");
    }
    public OnAppInterfaceUnregistered(Hashtable hash) {
        super(hash);
    }
    public AppInterfaceUnregisteredReason getReason() {
        Object obj = parameters.get(Names.reason);
        if (obj instanceof AppInterfaceUnregisteredReason) {
            return (AppInterfaceUnregisteredReason) obj;
        } else if (obj instanceof String) {
            AppInterfaceUnregisteredReason theCode = null;
            try {
                theCode = AppInterfaceUnregisteredReason.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.reason, e);
            }
            return theCode;
        }
        return null;
    }
    public void setReason( AppInterfaceUnregisteredReason reason ) {
        if (reason != null) {
            parameters.put(Names.reason, reason );
        }
    }
}
