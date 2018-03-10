#include "keyboard.h"
#include "scr_text.h"

const uint8_t* KEY_BINDING_QWERTY = {
	'\0', '1', '2', '3','4','5','6','7','8','9','0','?','\b',
	'\t','q','w','e','r','t','z','u','i','o','p','?','+',
	'?','a','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u',
	'u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u' 
};

KeyboardDriver::KeyboardDriver(InterruptManager* manager) : InterruptHandler(0x21, manager), dataPort(0x60),commandPort(0x64){
	while(commandPort.read() & 0x1) dataPort.read();
	commandPort.write(0xae); //activate interrupts
	commandPort.write(0x20); //gives current state
	uint8_t status = (dataPort.read() | 0x1) & ~0x10;
	commandPort.write(0x60); //change current state
	dataPort.write(status);
	dataPort.write(0xf4); //activate keyboard
	print("KeyboardDriver loaded.\n");
}

KeyboardDriver::~KeyboardDriver()
{}

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp) {
	uint8_t key = dataPort.read();
	if(key == 0xfa) { 
		// keyborad ready
	} else if(key < 0x80){
			if(key == 0x1c) print("\n");
			else {char* txt = "KEY RECIVED 0x??: ";
				char* hex = "0123456789abcdef";
				txt[14] = hex[(key>>4) & 0x0f];
				txt[15] = hex[key & 0x0f];
				txt[17] = KEY_BINDING_QWERTY[key];
				print(txt);
			}	
	} 
	return esp;
}