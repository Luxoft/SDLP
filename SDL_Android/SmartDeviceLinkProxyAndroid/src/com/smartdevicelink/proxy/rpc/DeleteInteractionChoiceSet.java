//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCRequest;
import com.smartdevicelink.proxy.constants.Names;

public class DeleteInteractionChoiceSet extends RPCRequest {

    public DeleteInteractionChoiceSet() {
        super("DeleteInteractionChoiceSet");
    }
    public DeleteInteractionChoiceSet(Hashtable hash) {
        super(hash);
    }
    public Integer getInteractionChoiceSetID() {
        return (Integer) parameters.get( Names.interactionChoiceSetID );
    }
    public void setInteractionChoiceSetID( Integer interactionChoiceSetID ) {
        if (interactionChoiceSetID != null) {
            parameters.put(Names.interactionChoiceSetID, interactionChoiceSetID );
        }
    }
}
