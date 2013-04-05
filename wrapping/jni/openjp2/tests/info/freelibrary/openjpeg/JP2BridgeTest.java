package info.freelibrary.openjpeg;

import static org.junit.Assert.*;

import java.io.File;

import org.junit.BeforeClass;
import org.junit.Test;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class JP2BridgeTest {

	private static final String EOL = System.getProperty("line.separator");
	private static final Logger LOGGER = LoggerFactory
			.getLogger(JP2BridgeTest.class);

	@BeforeClass
	public static void setUp() throws Exception {
		File logDir = new File("target/logs");
		if (!logDir.exists()) {
			if (!logDir.mkdirs()) {
				throw new RuntimeException("Couldn't create target/logs dir");
			}
		}
	}

	@Test
	public void testDecode() {
		JP2Bridge jp2Bridge = new JP2Bridge();

		// try {
		// File input = new File("/tmp/input");
		// File output = new File("/tmp/output");
		//
		// jp2Bridge.decode(jp2Bridge.getDecoding(input, output));
		// }
		// catch (Exception details) {
		// details.printStackTrace(System.err);
		// fail(details.getClass().getSimpleName() + ": " +
		// details.getMessage());
		// }
	}

	@Test
	public void testEncode() {
		JP2Bridge jp2Bridge = new JP2Bridge();

		try {
			File input = new File("/home/kevin/testimage.ppm");
			File output = new File("/tmp/testimage.jp2");

			jp2Bridge.encode(jp2Bridge.getEncoding(input, output));
		}
		catch (Exception details) {
			if (LOGGER.isDebugEnabled()) {
				LOGGER.debug(stringifyTrace(details));
			}
			
			fail(details.getMessage());
		}
	}
	
	private String stringifyTrace(Exception aException) {
		StringBuilder trace = new StringBuilder(aException.getMessage() + EOL);
		
		for (StackTraceElement details : aException.getStackTrace()) {
			StringBuilder message = new StringBuilder("   ");
			int lineNumber = details.getLineNumber();
			
			message.append(details.getClassName());
			
			if (lineNumber > 0) {
				message.append(" (").append(lineNumber).append(") ");
			}
			else if (details.isNativeMethod()) {
				message.append(" (native) ");
			}
			
			trace.append(message.append(EOL).toString());
		}
		
		return trace.toString();
	}

}
