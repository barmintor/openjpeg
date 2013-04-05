package info.freelibrary.openjpeg;

import java.io.File;

public class JP2Decoding extends Conversion {

	private String myInputFile;
	private String myOutputFile;
	
	public JP2Decoding(File aInputFile, File aOutputFile) {
		myInputFile = aInputFile.getAbsolutePath();
		myOutputFile = aOutputFile.getAbsolutePath();
	}

	public String getInputFile() {
		return myInputFile;
	}
	
	public String getOutputFile() {
		return myOutputFile;
	}

}
