//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCRequest;

public class UnregisterAppInterface extends RPCRequest {

    public UnregisterAppInterface() {
        super("UnregisterAppInterface");
    }
    public UnregisterAppInterface(Hashtable hash) {
        super(hash);
    }
}
