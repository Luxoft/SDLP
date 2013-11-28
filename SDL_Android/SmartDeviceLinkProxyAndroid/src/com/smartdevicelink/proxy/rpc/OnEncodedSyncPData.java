//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;
import java.util.Vector;


import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;

public class OnEncodedSyncPData extends RPCNotification {
	public OnEncodedSyncPData() {
        super("OnEncodedSyncPData");
    }
    public OnEncodedSyncPData(Hashtable hash) {
        super(hash);
    }
    
    public Vector<String> getData() {
    	if (parameters.get(Names.data) instanceof Vector<?>) {
    		Vector<?> list = (Vector<?>)parameters.get(Names.data);
    		if (list != null && list.size()>0) {
        		Object obj = list.get(0);
        		if (obj instanceof String) {
        			return (Vector<String>)list;
        		}
    		}
    	}
        return null;
    }
    
    public void setData( Vector<String> data ) {
        if (data != null) {
            parameters.put(Names.data, data );
        }
    }
}
