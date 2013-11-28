//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class AddSubMenuResponse extends RPCResponse {

    public AddSubMenuResponse() {
        super("AddSubMenu");
    }
    public AddSubMenuResponse(Hashtable hash) {
        super(hash);
    }
}
