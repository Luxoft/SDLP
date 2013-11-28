//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCStruct;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.SpeechCapabilities;
import com.smartdevicelink.util.DebugTool;

public class TTSChunk extends RPCStruct {

    public TTSChunk() { }
    public TTSChunk(Hashtable hash) {
        super(hash);
    }
    public String getText() {
        return (String) store.get( Names.text );
    }
    public void setText( String text ) {
        if (text != null) {
            store.put(Names.text, text );
        }
    }
    public SpeechCapabilities getType() {
        Object obj = store.get(Names.type);
        if (obj instanceof SpeechCapabilities) {
            return (SpeechCapabilities) obj;
        } else if (obj instanceof String) {
            SpeechCapabilities theCode = null;
            try {
                theCode = SpeechCapabilities.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.type, e);
            }
            return theCode;
        }
        return null;
    }
    public void setType( SpeechCapabilities type ) {
        if (type != null) {
            store.put(Names.type, type );
        }
    }
}
