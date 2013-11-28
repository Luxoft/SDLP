//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class AlertResponse extends RPCResponse {

    public AlertResponse() {
        super("Alert");
    }
    public AlertResponse(Hashtable hash) {
        super(hash);
    }
}
