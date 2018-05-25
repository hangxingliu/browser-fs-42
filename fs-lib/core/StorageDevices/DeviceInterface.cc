#include "DeviceInterface.h"

unsigned int DeviceInterface::getDeviceCapacity() { return 0; }
unsigned int DeviceInterface::getDeviceCurrentSize() { return 0; }

unsigned int DeviceInterface::read(unsigned int offset, unsigned int size, char *data) { return 0; }
unsigned int DeviceInterface::write(unsigned int offset, const char *data, unsigned int size) { return 0; }

DeviceInterface::~DeviceInterface() {}

