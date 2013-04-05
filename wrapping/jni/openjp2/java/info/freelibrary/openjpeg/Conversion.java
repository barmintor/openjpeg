package info.freelibrary.openjpeg;

import java.io.File;
import java.util.Arrays;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Conversion implements Constants {

	private static final Logger LOGGER = LoggerFactory
			.getLogger(Conversion.class);

	public int getFileFormat(File aFile) {
		return getFileFormat(aFile.getName());
	}

	public int getFileFormat(String aFileName) {
		// The 'extensions' array must be sorted for binarySearch to work
		String[] extensions = new String[] { "bmp", "j2c", "j2k", "jp2", "jpc",
				"pam", "pbm", "pgm", "pgx", "png", "pnm", "ppm", "raw", "rawl",
				"tga", "tif" };
		// The order of 'codes' array must match the order of 'extensions'
		int[] codes = new int[] { BMP_DFMT, J2K_CFMT, J2K_CFMT, JP2_CFMT,
				J2K_CFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, PGX_DFMT, PNG_DFMT,
				PXM_DFMT, PXM_DFMT, RAW_DFMT, RAWL_DFMT, TGA_DFMT, TIF_DFMT };
		int index = Arrays.binarySearch(extensions, getExtension(aFileName));

		if (LOGGER.isDebugEnabled()) {
			LOGGER.debug("OpenJPEG file format code: {}", index);
		}

		return index == -1 ? index : codes[index];
	}

	public String getExtension(String aFileName) {
		int dot = aFileName.lastIndexOf(".");

		if (dot != -1) {
			String ext = aFileName.substring(dot + 1, aFileName.length());

			if (LOGGER.isDebugEnabled()) {
				LOGGER.debug("OpenJPEG conversion file extension: {}", ext);
			}

			return ext;
		}

		return "";
	}
}
