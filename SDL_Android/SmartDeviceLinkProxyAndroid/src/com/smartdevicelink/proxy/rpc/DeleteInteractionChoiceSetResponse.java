//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class DeleteInteractionChoiceSetResponse extends RPCResponse {

    public DeleteInteractionChoiceSetResponse() {
        super("DeleteInteractionChoiceSet");
    }
    public DeleteInteractionChoiceSetResponse(Hashtable hash) {
        super(hash);
    }
}
