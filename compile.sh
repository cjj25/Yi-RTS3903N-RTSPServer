docker run --rm -it -v $(pwd)/build:/to_build cjj25/rsdk-4.8.5-5281-el /to_build/build.sh
if [ $? -ne 0 ]; then
    	echo "CMake reported an error, set CMAKE_VERBOSE_MAKEFILE to true and see the output"
	exit 1
fi
