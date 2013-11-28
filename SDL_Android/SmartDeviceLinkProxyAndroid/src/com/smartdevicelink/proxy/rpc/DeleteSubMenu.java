//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCRequest;
import com.smartdevicelink.proxy.constants.Names;

public class DeleteSubMenu extends RPCRequest {

    public DeleteSubMenu() {
        super("DeleteSubMenu");
    }
    public DeleteSubMenu(Hashtable hash) {
        super(hash);
    }
    public Integer getMenuID() {
        return (Integer) parameters.get( Names.menuID );
    }
    public void setMenuID( Integer menuID ) {
        if (menuID != null) {
            parameters.put(Names.menuID, menuID );
        }
    }
}
