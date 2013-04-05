FreeLibrary Java Wrapping for OpenJPEG
================================

This project is a repackaging of OpenJPEG.  The repackaging makes it available for use from within a Maven build. Included in the repackaging is a simple JNI layer over the image encode and decode functions. The JNI layer is basically just a shim and does not support all the functionality of the full OpenJPEG library.  The JNI wrapping is still in active development and not really ready for use.

&nbsp;&nbsp;&nbsp;&nbsp;You can find the OpenJPEG project at http://www.openjpeg.org  
&nbsp;&nbsp;&nbsp;&nbsp;You can find my (in process) Java layer at http://github.com/ksclarke/openjpeg


 Getting Started
-------------------------

To use the FreeLibrary Java Wrapping for OpenJPEG, check the repository out from GitHub:

    git clone http://github.com/ksclarke/openjpeg

Install Maven and Java 7's JDK on your machine and then build the project:

    cd openjpeg
    mvn install

You should see some unit tests run that confirm that the JNI layer is working.


 License
-------------------------

The FreeLibrary OpenJPEG Fork is released under the same license as the upstream project (the BSD 2-Clause License).

&nbsp;&nbsp;&nbsp;&nbsp;https://code.google.com/p/openjpeg/source/browse/trunk/LICENSE  
&nbsp;&nbsp;&nbsp;&nbsp;https://github.com/ksclarke/openjpeg/blob/develop/LICENSE


 Contact Information
-------------------------

If you're interested in the OpenJPEG library (the C code) you should ask questions at http://www.openjpeg.org/

If you're interested in the Java wrapping for OpenJPEG, feel free to ask me (<a href="mailto:ksclarke@gmail.com">Kevin S. Clarke</a>) questions.

