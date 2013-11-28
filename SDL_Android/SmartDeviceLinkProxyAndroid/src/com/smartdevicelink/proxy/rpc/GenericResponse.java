//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class GenericResponse extends RPCResponse {

    public GenericResponse() {
        super("GenericResponse");
    }
    public GenericResponse(Hashtable hash) {
        super(hash);
    }
}
