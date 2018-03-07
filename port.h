#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port {
protected:
	uint16_t portnumber;
	Port(uint16_t portnumber);
	~Port();
};

class Port8: Port {
protected:
	uint16_t portnumber;
	Port8(uint16_t portnumber);
	~Port8();
	virtual void write(uint8_t data);
	virtual uint8_t read();
};

class Port8Slow: Port8 {
public:
	uint16_t portnumber;
	Port8Slow(uint16_t portnumber);
	~Port8Slow();
	virtual void write(uint8_t data);
};

class Port16:Port {
public:
	uint16_t portnumber;
	Port16(uint16_t portnumber);
	~Port16();
	virtual void write(uint16_t data);
	virtual uint16_t read();
};

class Port32:Port {
public:
	uint16_t portnumber;
	Port32(uint16_t portnumber);
	~Port32();
	virtual void write(uint32_t data);
	virtual uint32_t read();
};



#endif