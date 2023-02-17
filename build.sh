#!/bin/bash

projectdir=$(pwd)
builddir=$projectdir/build

if [ "$1" = "clean" ]; then
        rm -rf $builddir
        exit 0
fi

if [ ! -d "$builddir" ]; then
        mkdir $builddir
fi

cc=g++
cmake -GNinja -B $builddir -S $projectdir
