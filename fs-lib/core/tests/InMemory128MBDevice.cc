#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include "../StorageDevices/InMemory128MBDevice.h"

using namespace std;

int testInMemory128MBDevice() {
	InMemory128MBDevice dev;

	if(dev.getDeviceCapacity() != dev.MAX_CAPACITY) {
		cout << "error: dev.getDeviceCapacity() != dev.MAX_CAPACITY" << endl;
		return 1;
	}

	if(dev.getDeviceCurrentSize() != dev.MAX_CAPACITY) {
		cout << "error: dev.getDeviceCurrentSize() != dev.MAX_CAPACITY" << endl;
		return 1;
	}

	dev = InMemory128MBDevice(32);
	if(dev.getDeviceCapacity() != 32) {
		cout << "error: dev.getDeviceCapacity() != 32" << endl;
		return 1;
	}

	string testStr("HelloWorld!");
	auto data = testStr.c_str();
	uint dataLen = (uint) testStr.length();

	uint wrote = dev.write(0, data, dataLen);
	if(wrote != dataLen) {
		cout << "error: wrote != dataLen" << endl;
		return 1;
	}

	wrote = dev.write(30, data, dataLen);
	if(wrote != 2) {
		cout << "error: wrote != 2" << endl;
		return 1;
	}

	wrote = dev.write(31, data, 1);
	if(wrote != 1) {
		cout << "error: wrote != 1" << endl;
		return 1;
	}

	wrote = dev.write(0, data, 0);
	if(wrote != 0) {
		cout << "error: wrote != 0" << endl;
		return 1;
	}

	char readData[32];
	uint read = dev.read(0, 5, readData);
	if(read != 5) {
		cout << "error: read != 5" << endl;
		return 1;
	}

	if(memcmp(readData, "Hello", 5) != 0) {
		cout << "error: memcmp(readData, \"Hello\", 5) != 0" << endl;
		return 1;
	}

	dev.write(30, data, dataLen);
	read = dev.read(30, 5, readData);
	if(read != 2) {
		cout << "error: read != 2" << endl;
		return 1;
	}

	if(memcmp(readData, "He", 2) != 0) {
		cout << "error: memcmp(readData, \"He\", 2) != 0" << endl;
		return 1;
	}

	return 0;
}
