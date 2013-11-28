//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;


import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.DriverDistractionState;
import com.smartdevicelink.util.DebugTool;

public class OnDriverDistraction  extends RPCNotification {
	public OnDriverDistraction() {
        super("OnDriverDistraction");
    }
    public OnDriverDistraction(Hashtable hash) {
        super(hash);
    }
    
    public DriverDistractionState getState() {
        Object obj = parameters.get(Names.state);
        if (obj instanceof DriverDistractionState) {
        	return (DriverDistractionState)obj;
        } else if(obj instanceof String) {
        	DriverDistractionState theCode = null;
        	try {
        		theCode = DriverDistractionState.valueForString((String) obj);
        	} catch (Exception e) {
                DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.state, e);
            }
        	return theCode;
        }    	
    	return null;
    }
    public void setState( DriverDistractionState state ) {
        if (state != null) {
            parameters.put(Names.state, state );
        }
    }  
}
