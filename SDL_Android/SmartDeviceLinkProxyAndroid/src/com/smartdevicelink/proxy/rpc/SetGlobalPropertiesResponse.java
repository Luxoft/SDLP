//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class SetGlobalPropertiesResponse extends RPCResponse {

    public SetGlobalPropertiesResponse() {
        super("SetGlobalProperties");
    }
    public SetGlobalPropertiesResponse(Hashtable hash) {
        super(hash);
    }
}
