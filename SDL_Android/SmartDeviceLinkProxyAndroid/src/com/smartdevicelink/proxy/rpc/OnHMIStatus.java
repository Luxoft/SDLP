//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.rpc;

import java.util.Hashtable;

import com.smartdevicelink.proxy.RPCNotification;
import com.smartdevicelink.proxy.constants.Names;
import com.smartdevicelink.proxy.rpc.enums.AudioStreamingState;
import com.smartdevicelink.proxy.rpc.enums.HMILevel;
import com.smartdevicelink.proxy.rpc.enums.SystemContext;
import com.smartdevicelink.util.DebugTool;

public class OnHMIStatus extends RPCNotification {
	private Boolean firstRun;
	
    public OnHMIStatus() {
        super("OnHMIStatus");
    }
    public OnHMIStatus(Hashtable hash) {
        super(hash);
    }
    public HMILevel getHmiLevel() {
        Object obj = parameters.get(Names.hmiLevel);
        if (obj instanceof HMILevel) {
            return (HMILevel) obj;
        } else if (obj instanceof String) {
            HMILevel theCode = null;
            try {
                theCode = HMILevel.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.hmiLevel, e);
            }
            return theCode;
        }
        return null;
    }
    public void setHmiLevel( HMILevel hmiLevel ) {
        if (hmiLevel != null) {
            parameters.put(Names.hmiLevel, hmiLevel );
        }
    }
    public AudioStreamingState getAudioStreamingState() {
        Object obj = parameters.get(Names.audioStreamingState);
        if (obj instanceof AudioStreamingState) {
            return (AudioStreamingState) obj;
        } else if (obj instanceof String) {
            AudioStreamingState theCode = null;
            try {
                theCode = AudioStreamingState.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.audioStreamingState, e);
            }
            return theCode;
        }
        return null;
    }
    public void setAudioStreamingState( AudioStreamingState audioStreamingState ) {
        if (audioStreamingState != null) {
            parameters.put(Names.audioStreamingState, audioStreamingState );
        }
    }
    public SystemContext getSystemContext() {
        Object obj = parameters.get(Names.systemContext);
        if (obj instanceof SystemContext) {
            return (SystemContext) obj;
        } else if (obj instanceof String) {
            SystemContext theCode = null;
            try {
                theCode = SystemContext.valueForString((String) obj);
            } catch (Exception e) {
            	DebugTool.logError("Failed to parse " + getClass().getSimpleName() + "." + Names.systemContext, e);
            }
            return theCode;
        }
        return null;
    }
    public void setSystemContext( SystemContext systemContext ) {
        if (systemContext != null) {
            parameters.put(Names.systemContext, systemContext );
        }
    }
    public Boolean getFirstRun() {
    	return this.firstRun;
    }
    public void setFirstRun(Boolean firstRun) {
    	this.firstRun = firstRun;
    }
}
