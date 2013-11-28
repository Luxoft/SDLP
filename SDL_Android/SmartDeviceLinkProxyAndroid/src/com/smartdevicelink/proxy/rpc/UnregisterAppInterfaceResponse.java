//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class UnregisterAppInterfaceResponse extends RPCResponse {

    public UnregisterAppInterfaceResponse() {
        super("UnregisterAppInterface");
    }
    public UnregisterAppInterfaceResponse(Hashtable hash) {
        super(hash);
    }
}
