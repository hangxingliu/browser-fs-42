# Reference from:
#   https://github.com/adevaykin/minimal-cmake-emscripten-project

cmake_minimum_required(VERSION 2.8)

project(emscripten-uint8-array-test)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)


# The following directive is duplicated with $CMAKE_TOOLCHAIN_FILE. But it is used for IDE intellisense
include_directories(${EMSCRIPTEN}/system/include)

file(GLOB CORE_SRC *.cc)
file(GLOB CORE_HDR *.h)

add_definitions("-std=c++11")
add_executable(test ${CORE_SRC} ${CORE_HDR})

set_target_properties(test PROPERTIES LINK_FLAGS
	"-s DEMANGLE_SUPPORT=1 --bind -s WASM=1")
