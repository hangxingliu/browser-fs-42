#ifndef CORE_DEVICE_INTERFACE_H
#define CORE_DEVICE_INTERFACE_H

#define out
class DeviceInterface {
public:
	virtual unsigned int getDeviceCapacity();
	virtual unsigned int getDeviceCurrentSize();
	virtual unsigned int read(unsigned int offset, unsigned int size, out char *data);
	virtual unsigned int write(unsigned int offset, const char *data, unsigned int size);
	virtual ~DeviceInterface();
};

#endif
