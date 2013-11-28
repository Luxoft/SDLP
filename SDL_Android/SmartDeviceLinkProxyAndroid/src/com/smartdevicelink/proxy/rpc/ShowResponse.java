//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class ShowResponse extends RPCResponse {

    public ShowResponse() {
        super("Show");
    }
    public ShowResponse(Hashtable hash) {
        super(hash);
    }
}
