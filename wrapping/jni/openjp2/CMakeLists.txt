find_package(Java REQUIRED)
find_package(JNI REQUIRED)

# Define our Java class (the OpenJPEG bridge class)
set(JAVA_CLASS info.freelibrary.openjpeg.JP2Bridge)

# Build the javah command
set(JAVAH_CMD ${Java_JAVAH_EXECUTABLE} -d ${CMAKE_CURRENT_SOURCE_DIR}
    -classpath ${CMAKE_CURRENT_SOURCE_DIR}/java ${JAVA_CLASS})

# Pull in the JNI includes
include_directories(
  ${JNI_INCLUDE_DIRS}
  ${OPENJPEG_BINARY_DIR}/src/lib/openjp2 # opj_config.h
  ${OPENJPEG_BINARY_DIR}/src/bin/common
  ${OPENJPEG_SOURCE_DIR}/src/bin/common
  ${OPENJPEG_SOURCE_DIR}/src/bin/jp2
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2
)

# Run javah on the Java class file
execute_process(
  COMMAND ${JAVAH_CMD}
  RESULT_VARIABLE RetVal
)

# Check that javah ran successfully
if(NOT ${RetVal} EQUAL 0)
  message(FATAL_ERROR "javah failed to successfully execute: ${JAVAH_CMD}")
endif()

# Build the C bridge code
add_library(jp2bridge SHARED
  jp2bridge.c
  ${OPENJPEG_SOURCE_DIR}/src/bin/common/opj_getopt.c
  ${OPENJPEG_SOURCE_DIR}/src/bin/jp2/convert.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/openjpeg.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/jp2.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/j2k.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/tcd.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/dwt.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/image.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/function_list.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/event.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/cio.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/pi.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/tgt.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/t1.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/mqc.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/raw.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/t2.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/bio.c
)