
#include "port.h"


Port::Port(uint16_t portnumber)
{
    this->portnumber = portnumber;
}

Port::~Port()
{
}





Port8::Port8(uint16_t portnumber)
    : Port(portnumber)
{
}

Port8::~Port8()
{
}

void Port8::write(uint8_t data)
{
    write8(portnumber, data);
}

uint8_t Port8::read()
{
    return read8(portnumber);
}





Port8Slow::Port8Slow(uint16_t portnumber)
    : Port8(portnumber)
{
}

Port8Slow::~Port8Slow()
{
}

void Port8Slow::write(uint8_t data)
{
    write8Slow(portnumber, data);
}





Port16::Port16(uint16_t portnumber)
    : Port(portnumber)
{
}

Port16::~Port16()
{
}

void Port16::write(uint16_t data)
{
    write16(portnumber, data);
}

uint16_t Port16::read()
{
    return read16(portnumber);
}





Port32::Port32(uint16_t portnumber)
    : Port(portnumber)
{
}

Port32::~Port32()
{
}

void Port32::write(uint32_t data)
{
    write32(portnumber, data);
}

uint32_t Port32::read()
{
    return read32(portnumber);
}

