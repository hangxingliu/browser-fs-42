cmake_minimum_required(VERSION 2.8)

project(browser-fs-42-cli)
set(TARGET_NAME "browser-fs-42-cli")

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES .
	../core/StorageDevices/*
	../core/FS*
	./*.cc
	./*.h
	)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
