//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.TriggerSource;
import com.smartdevicelink.util.DebugTool;

public class OnCommand extends RPCNotification {

    public OnCommand() {
        super("OnCommand");
    }
    public OnCommand(Hashtable hash) {
        super(hash);
    }
    public Integer getCmdID() {
        return (Integer) parameters.get( Names.cmdID );
    }
    public void setCmdID( Integer cmdID ) {
        if (cmdID != null) {
            parameters.put(Names.cmdID, cmdID );
        }
    }
    public TriggerSource getTriggerSource() {
        Object obj = parameters.get(Names.triggerSource);
        if (obj instanceof TriggerSource) {
            return (TriggerSource) obj;
        } else if (obj instanceof String) {
            TriggerSource theCode = null;
            try {
                theCode = TriggerSource.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.triggerSource, e);
            }
            return theCode;
        }
        return null;
    }
    public void setTriggerSource( TriggerSource triggerSource ) {
        if (triggerSource != null) {
            parameters.put(Names.triggerSource, triggerSource );
        }
    }
}
