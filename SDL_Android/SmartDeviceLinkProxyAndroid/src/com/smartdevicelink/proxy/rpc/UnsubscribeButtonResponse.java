//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class UnsubscribeButtonResponse extends RPCResponse {

    public UnsubscribeButtonResponse() {
        super("UnsubscribeButton");
    }
    public UnsubscribeButtonResponse(Hashtable hash) {
        super(hash);
    }
}
