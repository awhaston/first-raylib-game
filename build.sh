#!/bin/bash

if [[ ! -d "build" ]]; then
    echo "... Build folder not found ..."
    mkdir "build"

    cd "build"

    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

    cd ..
fi

cd "build"

make

./TestGame
