package info.freelibrary.openjpeg;

import java.io.File;

public class JP2Bridge {

	native void decode(JP2Decoding aDecoding);
	native void encode(JP2Encoding aEncoding);

	static {
        System.loadLibrary("jp2bridge");
    }

	/**
	 * A simple bridge between Java and OpenJPEG.
	 */
	public JP2Bridge() {}

	public JP2Encoding getEncoding(File aInputFile, File aOutputFile) {
		JP2Encoding encoding = new JP2Encoding(aInputFile, aOutputFile);

		// set some canned defaults

		return encoding;
	}

	public JP2Decoding getDecoding(File aInputFile, File aOutputFile) {
		JP2Decoding decoding = new JP2Decoding(aInputFile, aOutputFile);

		// set some canned defaults

		return decoding;
	}

}
