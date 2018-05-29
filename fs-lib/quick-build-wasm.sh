#!/usr/bin/env bash

# Please export Emscripten CMAKE_TOOLCHAIN_FILE path before this script. For example:
# 请在执行这个脚本之前导出 CMAKE_TOOLCHAIN_FILE 变量, 例如:
#
#   export CMAKE_TOOLCHAIN_FILE=/where/emsdk/emscripten/1.38.0/cmake/Modules/Platform/Emscripten.cmake
#   ./quick-build-wasm.sh
#
#

CMAKE_DIR="build-wasm"

function throw() { echo "fatal: ${1:-"exit with code 1"}"; exit 1; }

# checkout to directory same with this script
pushd `cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd` > /dev/null;

# Pre-check
if [[ -z "$CMAKE_TOOLCHAIN_FILE" ]]; then
	echo "Usage:";
	echo "    Please export Emscripten CMAKE_TOOLCHAIN_FILE path before this script. For example:";
	echo "";
	echo "        export CMAKE_TOOLCHAIN_FILE=/where/emsdk/emscripten/1.38.0/cmake/Modules/Platform/Emscripten.cmake";
	echo "        ./quick-build-wasm.sh";
	echo "";
	throw "\$CMAKE_TOOLCHAIN_FILE is empty!";
fi

if [[ ! -f "$CMAKE_TOOLCHAIN_FILE" ]]; then
	echo "\$CMAKE_TOOLCHAIN_FILE = $CMAKE_TOOLCHAIN_FILE";
	throw "\$CMAKE_TOOLCHAIN_FILE is not a file!";
fi

if [[ ! -d "$CMAKE_DIR" ]]; then
	mkdir "$CMAKE_DIR" || throw "Could not create \"$CMAKE_DIR\"";
fi

pushd $CMAKE_DIR;

# cmake
echo -e "\n[task]: cmake ../wasm -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE";
cmake ../wasm "-DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE" || throw "execute cmake failed!";

# make
if [[ -e "/proc/cpuinfo" ]]; then
	CPU_CORE=`grep -c ^processor /proc/cpuinfo`;
	if [[ -z "$CPU_CORE" ]]; then CPU_CORE="4"; fi
else
	CPU_CORE="4";
fi

echo -e "\n[task]: make -j$CPU_CORE";
make -j$CPU_CORE || throw "execute make failed!";

popd;

echo "all done!";


# restore directory path
popd > /dev/null;
