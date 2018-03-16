#ifndef __KEYBORAD_H
#define __KEYBORAD_H

#include "types.h"
#include "port.h"
#include "interrupts.h"
#include "driver.h"

class KeyboardDriver: public InterruptHandler, public Driver {
	Port8 dataPort;
	Port8 commandPort;
	bool keyDown[0x80];
public:
	KeyboardDriver(InterruptManager* manager);
	~KeyboardDriver();
	virtual uint32_t handleInterrupt(uint32_t esp);
	virtual void activate();
	//virtual void deactivate();
	//virtual void reset();

};
#endif