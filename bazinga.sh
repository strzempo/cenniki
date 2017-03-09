#!/bin/sh
#mkdir build
#cp layout.xml build/
cd build
make clean -j 7
#rm Makefile
set -e
qmake DEFINES+=EDITOR TARGET=editor ../cenniki.pro
make -j 7
#rm Makefile
make clean -j 7
qmake TARGET=cenniki ../cenniki.pro
make -j 7
#./editor
#./cenniki
