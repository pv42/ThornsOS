#ifndef __KEYBORAD_H
#define __KEYBORAD_H

#include "types.h"
#include "port.h"
#include "interrupts.h"

class KeyboardDriver: public InterruptHandler {
	Port8 dataPort;
	Port8 commandPort;
public:
	KeyboardDriver(InterruptManager* manager);
	~KeyboardDriver();
	virtual uint32_t handleInterrupt(uint32_t esp);
};
#endif