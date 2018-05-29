#!/usr/bin/env bash


CMAKE_DIR="build"

function throw() { echo "fatal: ${1:-"exit with code 1"}"; exit 1; }

# checkout to directory same with this script
pushd `cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd` > /dev/null;

if [[ -d "$CMAKE_DIR" ]]; then
	rm -rf "$CMAKE_DIR" || throw "Could not remove directory: \"$CMAKE_DIR\" !";
fi

if [[ -f "CMakeLists.txt.user" ]]; then
	rm -rf "CMakeLists.txt.user" || throw "Could not remove file: \"CMakeLists.txt.user\" !";
fi


echo "all done!";

# restore directory path
popd > /dev/null;
