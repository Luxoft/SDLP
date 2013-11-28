//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCResponse;

public class SpeakResponse extends RPCResponse {

    public SpeakResponse() {
        super("Speak");
    }
    public SpeakResponse(Hashtable hash) {
        super(hash);
    }
}
