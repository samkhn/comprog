#!/bin/bash
#set -x

if [ -x "$(command -v cindex)" ]; then
	cindex .
fi

pushd $(dirname $0)
PROJECT_DIR=$(pwd)
BUILD_DIR=$PROJECT_DIR/build

if [ ! -d "$BUILD_DIR" ]; then
	mkdir -p $BUILD_DIR
	cmake -B $BUILD_DIR -G Ninja -S $PROJECT_DIR
fi

cmake --build $BUILD_DIR

popd
