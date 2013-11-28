//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.protocol;

import java.nio.ByteBuffer;

import com.smartdevicelink.protocol.enums.FrameType;
import com.smartdevicelink.protocol.enums.SessionType;
import com.smartdevicelink.util.BitConverter;

public class ProtocolFrameHeader {
	private byte version = 1;
	private boolean compressed = false;
	private FrameType frameType = FrameType.Control;
	private SessionType sessionType = SessionType.RPC;
	private byte frameData = 0;
	private byte sessionID;
	private int dataSize;
	private int messageID;
	
	public static final byte FrameDataSingleFrame = 0x00;
	public static final byte FrameDataFirstFrame = 0x00;
	public static final byte FrameDataFinalConsecutiveFrame = 0x00;
	
	public ProtocolFrameHeader() {}
	
	public static ProtocolFrameHeader parseWiProHeader(byte[] header) {
		ProtocolFrameHeader msg = new ProtocolFrameHeader();
		
		byte version = (byte) (header[0] >>> 4);
		msg.setVersion(version);
		
		boolean compressed = 1 == ((header[0] & 0x08) >>> 3);
		msg.setCompressed(compressed);
		
		byte frameType = (byte) (header[0] & 0x07);
		msg.setFrameType(FrameType.valueOf(frameType));
		
		byte serviceType = header[1];
		msg.setSessionType(SessionType.valueOf(serviceType));
		
		byte frameData = header[2];
		msg.setFrameData(frameData);
		
		byte sessionID = header[3];
		msg.setSessionID(sessionID);
		
		int dataSize = BitConverter.intFromByteArray(header, 4);
		msg.setDataSize(dataSize);
		
		if (version == 2) {
			int messageID = BitConverter.intFromByteArray(header, 8);
			msg.setMessageID(messageID);
		} else msg.setMessageID(0);
		
		return msg;
	}
	
	protected byte[] assembleHeaderBytes() {
		int header = 0;
		header |= version;
		header <<= 1;
		header |= (compressed ? 1 : 0);
		header <<= 3;
		header |= frameType.value();
		header <<= 8;
		header |= sessionType.value();
        header <<= 8;
        /**
         * The byte ("frameData") is implicitly cast to int, and if it is
         * negative (more than 127), first two bytes of the header will get
         * screwed; that's why it is un-signed with 0xFF first
         */
        header |= frameData & 0xFF;
		header <<= 8;
		header |= sessionID;
		if (version == 1) {
		    return ByteBuffer.allocate(8).putInt(header).putInt(dataSize).array();
		} else if (version == 2) {
            return ByteBuffer.allocate(12).putInt(header).putInt(dataSize).putInt(messageID).array();
		} else return null;
	}
	
	public String toString() {
		String ret = "";
		ret += "version " + version + ", " + (compressed ? "compressed" : "uncompressed") + "\n";
		ret += "frameType " + frameType + ", serviceType " + sessionType;
		ret += "\nframeData " + frameData;
		ret += ", sessionID " + sessionID;
		ret += ", dataSize " + dataSize;
		ret += ", messageID " + messageID;
		return ret;
	}
	
	public byte getVersion() {
		return version;
	}

	public void setVersion(byte version) {
		this.version = version;
	}

	public boolean isCompressed() {
		return compressed;
	}

	public void setCompressed(boolean compressed) {
		this.compressed = compressed;
	}

	public byte getFrameData() {
		return frameData;
	}

	public void setFrameData(byte frameData) {
		this.frameData = frameData;
	}

	public byte getSessionID() {
		return sessionID;
	}

	public void setSessionID(byte sessionID) {
		this.sessionID = sessionID;
	}

	public int getDataSize() {
		return dataSize;
	}

	public void setDataSize(int dataSize) {
		this.dataSize = dataSize;
	}

	public int getMessageID() {
		return messageID;
	}

	public void setMessageID(int messageID) {
		this.messageID = messageID;
	}

	public FrameType getFrameType() {
		return frameType;
	}

	public void setFrameType(FrameType frameType) {
		this.frameType = frameType;
	}

	public SessionType getSessionType() {
		return sessionType;
	}

	public void setSessionType(SessionType sessionType) {
		this.sessionType = sessionType;
	}
}
