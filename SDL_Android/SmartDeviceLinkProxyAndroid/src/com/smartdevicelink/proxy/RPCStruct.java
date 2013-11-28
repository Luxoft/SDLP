//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy;

import java.util.Hashtable;

import org.json.JSONException;
import org.json.JSONObject;

import com.smartdevicelink.marshal.JsonRPCMarshaller;
import com.smartdevicelink.proxy.constants.Names;

public class RPCStruct {

	protected Hashtable<String, Object> store = null;
	
	public RPCStruct() {
		store = new Hashtable<String, Object>();
	}
	
	protected RPCStruct(RPCStruct rpcs) {
		this.store = rpcs.store;
	}
	
	public RPCStruct(Hashtable<String, Object> hashtable) {
		store = hashtable;
	}
	
	public void deserializeJSON(JSONObject jsonObject) throws JSONException {
		store = JsonRPCMarshaller.deserializeJSONObject(jsonObject);
	}
	
	// deserializeJSONObject method moved to JsonRPCMarshaller for consistency
	// Keep reference here for backwards compatibility
	@Deprecated
	public static Hashtable<String, Object> deserializeJSONObject(JSONObject jsonObject) 
			throws JSONException {
		return JsonRPCMarshaller.deserializeJSONObject(jsonObject);
	}
	
	public JSONObject serializeJSON() throws JSONException {
		return JsonRPCMarshaller.serializeHashtable(store);
	}
	
	public JSONObject serializeJSON(byte version) throws JSONException {
		if (version == 2) {
			String messageType = (String)store.keys().nextElement();
			Hashtable function = (Hashtable)store.get(messageType);
			Hashtable hash = (Hashtable)function.get(Names.parameters);
			return JsonRPCMarshaller.serializeHashtable(hash);
		} else return JsonRPCMarshaller.serializeHashtable(store);
	}
}
