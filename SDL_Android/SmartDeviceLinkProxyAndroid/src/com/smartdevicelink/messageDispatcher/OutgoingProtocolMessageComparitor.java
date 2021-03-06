//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.messageDispatcher;

import java.util.Comparator;

import com.smartdevicelink.protocol.ProtocolMessage;

public class OutgoingProtocolMessageComparitor implements Comparator<ProtocolMessage> {

	@Override
	public int compare(ProtocolMessage arg0, ProtocolMessage arg1) {
		// FIFO order
		// TODO change to simple LinkedBlockingQueue
		return arg0.getCreationTime().compareTo(arg1.getCreationTime());
	}
}

