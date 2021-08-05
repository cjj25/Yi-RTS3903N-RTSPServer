#!/bin/bash
# /toolchains/sdk/activate
rm -rf to_sd
cd /to_build/
rm -rf output
mkdir output && cd output
cmake ..
make clean && make
if [ $? -ne 0 ]; then
    	echo "CMake reported an error, set CMAKE_VERBOSE_MAKEFILE to true and see the output"
	exit 1
fi

cd ..
rm -rf output
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
cp -R _install/bin/rRTSPServer /to_build/to_sd/
echo "Grabber and RTSPServer compiled, creating payload for SD card"
cd /to_build/sd_payload
rm -rf Factory
rm -rf /to_build/sd_payload/root
git clone https://github.com/cjj25/yi-hack-telnet-root root
if [ $? -ne 0 ]; then
    	echo "Problem cloning the payload repo"
	exit 1
fi
cp -R root/Factory .
cp *.conf *.sh Factory/
chmod +x Factory/*
mv Factory /to_build/to_sd/ && chmod +x /to_build/to_sd/
cd /to_build/to_sd/
tar cvzf /to_build/release/Yi-RTS3903N-RTSPServerV01.tar.gz .


	

