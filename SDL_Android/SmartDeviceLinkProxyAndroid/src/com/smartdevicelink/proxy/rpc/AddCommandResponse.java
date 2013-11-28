//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class AddCommandResponse extends RPCResponse {

    public AddCommandResponse() {
        super("AddCommand");
    }
    public AddCommandResponse(Hashtable hash) {
        super(hash);
    }
}

