//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.TBTState;
import com.smartdevicelink.util.DebugTool;

public class OnTBTClientState extends RPCNotification {

    public OnTBTClientState() {
        super("OnTBTClientState");
    }
    public OnTBTClientState(Hashtable hash) {
        super(hash);
    }
    public TBTState getState() {
        Object obj = parameters.get(Names.state);
        if (obj instanceof TBTState) {
        	return (TBTState)obj;
        } else if(obj instanceof String) {
        	TBTState theCode = null;
        	try{
        		theCode = TBTState.valueForString((String) obj);
        	} catch (Exception e) {
                DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.state, e);
            }
        	return theCode;
        }    	
    	return null;
    }
    public void setState( TBTState state ) {
        if (state != null) {
            parameters.put(Names.state, state );
        }
    }
} // end-class
