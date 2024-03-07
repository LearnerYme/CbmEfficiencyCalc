#!/bin/bash

if [ $# -eq 1 ] && [ $1 = "uninstall" ]; then
    echo "[Uninstall]"
    rm -rf build
else 
    echo "[Install] Initilizing..."
    echo "[Contact] yi.huang@gsi.de"

    if [ ! -d build ]; then
        mkdir build
    fi

    cdir=`pwd`

    echo $cdir

    echo "[Install] generating Makefile..."
    cd $cdir/build && cmake ../src
    echo "[Install] Done"

    echo "[Install]: compiling..."
    cd $cdir/build && make
    echo "[Install] Done"

    unset cdir
fi