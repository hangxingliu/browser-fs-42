#include "DeviceInterface.h"

#ifndef IN_MEMORY_128_MB_DEVICE_H
#define IN_MEMORY_128_MB_DEVICE_H

class InMemory128MBDevice: public DeviceInterface {
	unsigned int capacity = MAX_CAPACITY;
public: // methods
	const static unsigned int MAX_CAPACITY = 1024 * 1024 * 128;
	char* data;

	InMemory128MBDevice(unsigned int capacity = MAX_CAPACITY);
	~InMemory128MBDevice();

public: //interfaces
	unsigned int getDeviceCapacity() { return capacity; }
	unsigned int getDeviceCurrentSize() { return capacity; }
	unsigned int read(unsigned int offset, unsigned int size, char *data);
	unsigned int write(unsigned int offset, const char *data, unsigned int size);
};

#endif
