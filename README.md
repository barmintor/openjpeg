=================================================================================
 FreeLibrary OpenJPEG Fork   2.0.0-SNAPSHOT   http://github.com/ksclarke/openjpeg
=================================================================================

This project is a repackaging of OpenJPEG so that it can be used within a Maven
build. Included is a simple JNI layer over the image encode and decode functions.
The JNI layer is basically just a shim and does not support all the functionality
of the full OpenJPEG library.


=================================================================================
 Getting Started
=================================================================================

To use the FreeLibrary OpenJPEG Fork, check the repository out from GitHub:

  git clone http://github.com/ksclarke/openjpeg

Install Maven and Java 7's JDK on your machine and then build the project:

  cd openjpeg
  mvn install

You should see some unit tests run that confirm that the JNI layer is working.


=================================================================================
 License
=================================================================================

The FreeLibrary OpenJPEG Fork is released under the same license as the upstream
project (the BSD 2-Clause License).

  https://code.google.com/p/openjpeg/source/browse/trunk/LICENSE
  https://github.com/ksclarke/openjpeg/blob/develop/LICENSE (mirror)


=================================================================================
 Contact
=================================================================================

Kevin S. Clarke <ksclarke@gmail.com>

