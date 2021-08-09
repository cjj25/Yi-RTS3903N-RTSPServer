#!/bin/bash
# /toolchains/sdk/activate
OUTPUT_DIR=/to_build/
TMP_BUILD_DIR=$OUTPUT_DIR/output/
SD_CARD_OUTPUT=$OUTPUT_DIR/to_sd/
SD_CARD_PAYLOAD=$OUTPUT_DIR/sd_payload/

# Remove the current sd output folder if it exists
rm -rf $SD_CARD_OUTPUT
mkdir -p $SD_CARD_OUTPUT

# Move to our output directory and create a tempory build folder
cd $OUTPUT_DIR
rm -rf $TMP_BUILD_DIR
mkdir $TMP_BUILD_DIR && cd $TMP_BUILD_DIR

# Compile source
cmake ..
make clean && make
if [ $? -ne 0 ]; then
    	echo "CMake reported an error, set CMAKE_VERBOSE_MAKEFILE to true and see the output"
	exit 1
fi

# Cleanup temporary folder
cd ..
rm -rf $TMP_BUILD_DIR

echo "Build stream grabber complete, compiling RTSPServer"
# Activate the full build env
source /toolchains/sdk/activate
cd src/rRTSPServer
./cleanup.rRTSPServer
./init.rRTSPServer
./compile.rRTSPServer
if [ $? -ne 0 ]; then
    	echo "Problem compiling RTSPServer"
	exit 1
fi
# Move binary to sd output folder
cp -R _install/bin/rRTSPServer $SD_CARD_OUTPUT
echo "Grabber and RTSPServer compiled, creating payload for SD card"

# Move to SD payload folder
cd $SD_CARD_PAYLOAD
#rm -rf Factory
#rm -rf /to_build/sd_payload/root
#git clone https://github.com/cjj25/yi-hack-telnet-root root
#if [ $? -ne 0 ]; then
#    	echo "Problem cloning the payload repo"
#	exit 1
#fi

#cp -R root/Factory .
#cp *.conf *.sh Factory/
#chmod +x Factory/*
cp -R * $SD_CARD_OUTPUT
chmod +x $SD_CARD_OUTPUT/wifi/*
chmod +x $SD_CARD_OUTPUT/Yi/*

#mv Factory /to_build/to_sd/ && chmod +x /to_build/to_sd/
cd $SD_CARD_OUTPUT
chmod -R 777 *
tar cvzf /to_build/release/Yi-RTS3903N-RTSPServerV03.tar.gz .


	

