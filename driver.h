#ifndef __DRIVER_H
#define __DRIVER_H

#include "types.h"

class Driver {
public:
	Driver();
	~Driver();
	virtual void activate();
	virtual void deactivate();
	virtual uint32_t reset();
};

class DriverManager {
private:
	Driver* drivers[255];
	int driverCount;

public:
	DriverManager();
	void addDriver(Driver* driver);
	void activateAll();
};

#endif