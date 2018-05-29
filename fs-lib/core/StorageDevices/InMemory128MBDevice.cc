#include "memory"
#include "cstring"
#include "../Base/Types.h"
#include "InMemory128MBDevice.h"

using namespace std;

InMemory128MBDevice::InMemory128MBDevice(unsigned int capacity) {
	if(capacity > MAX_CAPACITY)
		capacity = MAX_CAPACITY;
	this->capacity = capacity;

	data = (char*) malloc(sizeof(char*) * capacity);
	if(!data)
		this->capacity = 0;
}

InMemory128MBDevice::~InMemory128MBDevice() {
	if(!data) return;
	free(data);
	data = nullptr;
}

unsigned int InMemory128MBDevice::read(unsigned int offset, unsigned int size, char *data) {
	if(size == 0) return 0;
	if(offset >= capacity) return 0;

	uint realSize = size;
	if(offset + size > capacity)
		realSize = capacity - offset;

	if(data) memcpy(data, this->data + offset, realSize);
	return realSize;

}

unsigned int InMemory128MBDevice::write(unsigned int offset, const char *data, unsigned int size) {
	if(!data) return 0;
	if(size == 0) return 0;
	if(offset >= capacity) return 0;

	uint realSize = size;
	if(offset + size > capacity)
		realSize = capacity - offset;

	memcpy(this->data + offset, data, realSize);
	return realSize;
}
