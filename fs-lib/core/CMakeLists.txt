cmake_minimum_required(VERSION 2.8)

project(browser-fs-42-core)
set(TARGET_NAME "browser-fs-42-core-test")

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES .
	tests/*.cc
	tests/*.h
	StorageDevices/DeviceInterface.cc
	StorageDevices/DeviceInterface.h
	StorageDevices/InMemory128MBDevice.cc
	StorageDevices/InMemory128MBDevice.h
	)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
