//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCStruct;
import com.smartdevicelink.proxy.constants.Names;

public class StartTime extends RPCStruct {

    public StartTime() { }
    public StartTime(Hashtable hash) {
        super(hash);
    }
    public Integer getHours() {
        return (Integer) store.get( Names.hours );
    }
    public void setHours( Integer hours ) {
        if (hours != null) {
            store.put(Names.hours, hours );
        }
    }
    public Integer getMinutes() {
        return (Integer) store.get( Names.minutes );
    }
    public void setMinutes( Integer minutes ) {
        if (minutes != null) {
            store.put(Names.minutes, minutes );
        }
    }
    public Integer getSeconds() {
        return (Integer) store.get( Names.seconds );
    }
    public void setSeconds( Integer seconds ) {
        if (seconds != null) {
            store.put(Names.seconds, seconds );
        }
    }
}
