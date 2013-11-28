//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class SubscribeButtonResponse extends RPCResponse {

    public SubscribeButtonResponse() {
        super("SubscribeButton");
    }
    public SubscribeButtonResponse(Hashtable hash) {
        super(hash);
    }
}
