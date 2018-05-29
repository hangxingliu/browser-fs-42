cmake_minimum_required(VERSION 2.8)

project(browser-fs-42-core)
set(TARGET_NAME "browser-fs-42-core-test")

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES .
	tests/*
	StorageDevices/*
	FS*
	)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
