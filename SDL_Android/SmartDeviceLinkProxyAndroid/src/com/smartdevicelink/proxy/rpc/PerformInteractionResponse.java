//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.TriggerSource;
import com.smartdevicelink.util.DebugTool;

public class PerformInteractionResponse extends RPCResponse {

    public PerformInteractionResponse() {
        super("PerformInteraction");
    }
    public PerformInteractionResponse(Hashtable hash) {
        super(hash);
    }
    public Integer getChoiceID() {
        return (Integer) parameters.get( Names.choiceID );
    }
    public void setChoiceID( Integer choiceID ) {
        if (choiceID != null) {
            parameters.put(Names.choiceID, choiceID );
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
