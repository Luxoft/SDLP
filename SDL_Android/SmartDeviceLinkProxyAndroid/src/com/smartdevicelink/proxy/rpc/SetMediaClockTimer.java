//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCRequest;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.UpdateMode;
import com.smartdevicelink.util.DebugTool;

public class SetMediaClockTimer extends RPCRequest {

    public SetMediaClockTimer() {
        super("SetMediaClockTimer");
    }
    public SetMediaClockTimer(Hashtable hash) {
        super(hash);
    }
    public StartTime getStartTime() {
        Object obj = parameters.get(Names.startTime);
        if (obj instanceof StartTime) {
        	return (StartTime)obj;
        } else if (obj instanceof Hashtable) {
        	return new StartTime((Hashtable)obj);
        }
        return null;
    }
    public void setStartTime( StartTime startTime ) {
        if (startTime != null) {
            parameters.put(Names.startTime, startTime );
        }
    }
    public UpdateMode getUpdateMode() {
        Object obj = parameters.get(Names.updateMode);
        if (obj instanceof UpdateMode) {
            return (UpdateMode) obj;
        } else if (obj instanceof String) {
            UpdateMode theCode = null;
            try {
                theCode = UpdateMode.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.updateMode, e);
            }
            return theCode;
        }
        return null;
    }
    public void setUpdateMode( UpdateMode updateMode ) {
        if (updateMode != null) {
            parameters.put(Names.updateMode, updateMode );
        }
    }
}
