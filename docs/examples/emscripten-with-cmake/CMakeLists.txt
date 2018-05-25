# Reference from:
#   https://github.com/adevaykin/minimal-cmake-emscripten-project

cmake_minimum_required(VERSION 2.8)

project(emscripten-with-cmake-test)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

# include_directories("lib/assimp/include")
# link_directories("lib/assimp/lib-js")
# link_libraries("assimp")

file(GLOB CORE_HDR main.cc)

add_definitions("-std=c++11")
add_executable(test ${CORE_SRC} ${CORE_HDR})

set_target_properties(test PROPERTIES LINK_FLAGS
	"-s DEMANGLE_SUPPORT=1 --bind -s WASM=1 \
	-s EXPORTED_FUNCTIONS=\"['_export_main']\" -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\" ")
