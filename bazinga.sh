#!/bin/sh
#mkdir build
#cp layout.xml build/
cd build
make clean
rm Makefile
set -e
qmake ../cenniki.pro
make -j 7
./cenniki
