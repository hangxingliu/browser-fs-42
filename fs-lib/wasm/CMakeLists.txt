cmake_minimum_required(VERSION 2.8)

project(browser-fs-42-wasm)
set(TARGET_NAME "browser-fs-42-wasm")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../wasm-dist)

# SET(CMAKE_C_COMPILER emcc)
# SET(CMAKE_CXX_COMPILER em++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

file(GLOB SOURCE_FILES .
	../core/StorageDevices/*
	../core/FS*
	./*.cc
	)

add_executable(${TARGET_NAME} ${SOURCE_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS
	"-s DEMANGLE_SUPPORT=1 --bind -s WASM=1 \
	-s EXPORTED_FUNCTIONS=\"['_export_main']\" -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\" ")
