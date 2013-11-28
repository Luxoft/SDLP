//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.util;

import java.nio.ByteBuffer;

public class BitConverter {
	public static String bytesToHex(byte [] bytes) {
		return bytesToHex(bytes, 0, bytes.length);
	} // end-method

	public static String bytesToHex(byte[] bytes, int offset, int length) {
		if (bytes == null) { return null; }
		final char[] HexDigits = new char[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
		byte b;
		char[] hexChars = new char[2 * length];
		//StringBuffer sb = new StringBuffer();
		int upperBound = Math.min(bytes.length, (offset + length));
		int baidx = 0;
		int sidx = 0;
		for (baidx = offset; baidx < upperBound; baidx++) {
			// Get the byte from the array
			b = bytes[baidx];
			// Use nibbles as index into hex digit array (left nibble, then right)
			hexChars[sidx++] = HexDigits[(b & 0xf0) >> 4];
			hexChars[sidx++] = HexDigits[(b & 0x0f)];
		} // end-for
		return new String(hexChars);
	} // end-method

	public static byte [] hexToBytes(String hexString) {
		if (hexString == null) { return null; }
		if (hexString.length() % 2 != 0) {
			hexString = "0" + hexString;
		}
		byte [] theBytes = new byte[hexString.length() / 2];
		for (int i = 0; i < hexString.length(); i += 2) {
			String byteString = hexString.substring(i, i + 2);
			byte theByte = (byte)Integer.parseInt(byteString, 16);
			theBytes[i/2] = theByte;
		}
		return theBytes;
	} // end-method

	public static final byte[] intToByteArray(int value) {
	    return ByteBuffer.allocate(4).putInt(value).array();
	}
	
	public static int intFromByteArray(byte[] sizeBuf, int offset) {
	    return ByteBuffer.wrap(sizeBuf, offset, 4).getInt();
    }

	public static final byte[] shortToByteArray(short value) {
        return ByteBuffer.allocate(2).putShort(value).array();
	}
	
	public static short shortFromByteArray(byte[] sizeBuf, int offset) {
        return ByteBuffer.wrap(sizeBuf, offset, 2).getShort();
    }
}
