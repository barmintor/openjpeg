package info.freelibrary.openjpeg;

import java.io.File;

public class JP2Encoding extends Conversion {

	private String myInputFile;
	private String myOutputFile;
	private boolean myImageNeedsTiles;
	
	public JP2Encoding(File aInputFile, File aOutputFile) {
		this(aInputFile, aOutputFile, true);
	}
	
	public JP2Encoding(File aInputFile, File aOutputFile, boolean aTiledJP2) {
		myInputFile = aInputFile.getAbsolutePath();
		myOutputFile = aOutputFile.getAbsolutePath();
		myImageNeedsTiles = aTiledJP2;
	}
	
	public String getInputFile() {
		return myInputFile;
	}

	public String getOutputFile() {
		return myOutputFile;
	}

	public boolean createTiles() {
		return myImageNeedsTiles;
	}

	public int getSourceFormat() {
		return getFileFormat(myInputFile);
	}
	
	public int getTargetFormat() {
		return getFileFormat(myOutputFile);
	}

}
