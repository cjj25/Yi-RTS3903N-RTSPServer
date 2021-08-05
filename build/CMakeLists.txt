cmake_minimum_required(VERSION 3.19)
project(RTS3903N_RTSP)
set(SOURCE_FILES src/stream.c headers)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSROOT /toolchains/sdk/mips-linux-uclibc)
set(CMAKE_C_COMPILER /toolchains/sdk/bin/mips-linux-gcc)
set(CMAKE_CXX_COMPILER /toolchains/sdk/bin/mips-linux-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/to_sd/)

add_executable(stream ${SOURCE_FILES})

include_directories(headers lib)
target_link_libraries(stream -L${PROJECT_SOURCE_DIR}/lib/ -lrtsio -lopus -lrtsjpeg -lsbc -lasound -lrtsgeom -lrtstream -lrtsv4l2 -lrtscamkit -lh1encoder -lrtsosd -lrtsutils -lrtsosd2 -lrtsjpeg -lrtsisp -lrtsaec )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=5281 -Wl,-rpath-link=${PROJECT_SOURCE_DIR}/lib/")
set(CMAKE_VERBOSE_MAKEFILE FALSE)

add_custom_command(
        TARGET stream
        PRE_BUILD
        COMMAND rm -Rf ${OUTPUT_DIR}
        COMMENT "Cleaning output directory"
)
# TODO: Fix the static building so the dynamic linking mess isn't required
add_custom_command(
        TARGET stream
        POST_BUILD
	COMMENT "Copying libs and bins to output"
	COMMAND mkdir -p ${OUTPUT_DIR}
	COMMAND cp stream ${OUTPUT_DIR}/stream
	COMMAND cp -R ${PROJECT_SOURCE_DIR}/lib ${OUTPUT_DIR}/lib
	COMMAND rm -rf stream
        COMMENT "Fixing annoying dynamic linker issues"
	COMMAND mv ${OUTPUT_DIR}/lib/librtsio.so ${OUTPUT_DIR}/lib/librtsio.so.0
	COMMAND mv ${OUTPUT_DIR}/lib/librtsjpeg.so ${OUTPUT_DIR}/lib/librtsjpeg.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtsgeom.so ${OUTPUT_DIR}/lib/librtsgeom.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtstream.so ${OUTPUT_DIR}/lib/librtstream.so.2
	COMMAND mv ${OUTPUT_DIR}/lib/librtsv4l2.so ${OUTPUT_DIR}/lib/librtsv4l2.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtscamkit.so ${OUTPUT_DIR}/lib/librtscamkit.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/libh1encoder.so ${OUTPUT_DIR}/lib/libh1encoder.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtsosd.so ${OUTPUT_DIR}/lib/librtsosd.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtsutils.so ${OUTPUT_DIR}/lib/librtsutils.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/librtsosd2.so ${OUTPUT_DIR}/lib/librtsosd2.so.0
	COMMAND mv ${OUTPUT_DIR}/lib/librtsisp.so ${OUTPUT_DIR}/lib/librtsisp.so.1
	COMMAND mv ${OUTPUT_DIR}/lib/libasound.so ${OUTPUT_DIR}/lib/libasound.so.2
	COMMAND mv ${OUTPUT_DIR}/lib/libopus.so ${OUTPUT_DIR}/lib/libopus.so.0
	COMMAND mv ${OUTPUT_DIR}/lib/libsbc.so ${OUTPUT_DIR}/lib/libsbc.so.1
	COMMAND cp /toolchains/sdk/lib/libstdc++.so.6 ${OUTPUT_DIR}/lib/
	COMMAND cp /toolchains/sdk/lib/libatomic.so.1 ${OUTPUT_DIR}/lib/
)
