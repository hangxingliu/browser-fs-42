#!/usr/bin/env bash

# checkout to directory same with this script
command pushd `cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd` > /dev/null;

function throw() { echo "fatal: ${1:-"exit with code 1"}"; exit 1; }

[[ -d "build" ]] || mkdir build || throw;

cd build;

cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/emsdk/emscripten/1.38.0/cmake/Modules/Platform/Emscripten.cmake || throw;

make -j16 || throw;

echo "all done!";

# restore directory path
command popd > /dev/null;
