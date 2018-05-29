#!/usr/bin/env bash

# Please export Emscripten EMSCRIPTEN path before this script. For example:
# 请在执行这个脚本之前导出 EMSCRIPTEN 变量, 例如:
#
#   export EMSCRIPTEN=/where/emsdk/emscripten/1.38.0
#   ./build.sh
#
#

CMAKE_DIR="build"

function throw() { echo "fatal: ${1:-"exit with code 1"}"; exit 1; }

# checkout to directory same with this script
pushd `cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd` > /dev/null;

# Pre-check
if [[ -z "$EMSCRIPTEN" ]]; then
	echo "Usage:";
	echo "    Please export Emscripten EMSCRIPTEN path before this script. For example:";
	echo "";
	echo "        export EMSCRIPTEN=/where/emsdk/emscripten/1.38.0";
	echo "        ./build.sh";
	echo "";
	throw "\$EMSCRIPTEN is empty!";
fi

if [[ ! -d "$EMSCRIPTEN" ]]; then
	echo "\$EMSCRIPTEN = $EMSCRIPTEN";
	throw "\$EMSCRIPTEN is not a directory!";
fi

CMAKE_TOOLCHAIN_FILE="$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake"
if [[ ! -f "$CMAKE_TOOLCHAIN_FILE" ]]; then
	echo "\$CMAKE_TOOLCHAIN_FILE = $CMAKE_TOOLCHAIN_FILE";
	throw "\$CMAKE_TOOLCHAIN_FILE is not a directory!";
fi

if [[ ! -d "$CMAKE_DIR" ]]; then
	mkdir "$CMAKE_DIR" || throw "Could not create \"$CMAKE_DIR\"";
fi

pushd $CMAKE_DIR;

# cmake
echo -e "\n[task]: cmake .. -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE";
cmake .. "-DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE" || throw "execute cmake failed!";

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
