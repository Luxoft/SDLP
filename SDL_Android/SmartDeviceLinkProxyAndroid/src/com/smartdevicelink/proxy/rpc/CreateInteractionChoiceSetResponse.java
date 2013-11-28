//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class CreateInteractionChoiceSetResponse extends RPCResponse {

    public CreateInteractionChoiceSetResponse() {
        super("CreateInteractionChoiceSet");
    }
    public CreateInteractionChoiceSetResponse(Hashtable hash) {
        super(hash);
    }
}
