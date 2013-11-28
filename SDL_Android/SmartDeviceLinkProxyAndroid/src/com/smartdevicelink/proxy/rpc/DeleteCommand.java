//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCRequest;
import com.smartdevicelink.proxy.constants.Names;

public class DeleteCommand extends RPCRequest {

    public DeleteCommand() {
        super("DeleteCommand");
    }
    public DeleteCommand(Hashtable hash) {
        super(hash);
    }
    public Integer getCmdID() {
        return (Integer) parameters.get( Names.cmdID );
    }
    public void setCmdID( Integer cmdID ) {
        if (cmdID != null) {
            parameters.put(Names.cmdID, cmdID );
        }
    }
}
