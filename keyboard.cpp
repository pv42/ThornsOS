#include "keyboard.h"
#include "scr_text.h"

#define KEY_LSHIFT 0x2a

const uint8_t KEY_BINDING_QWERTY[0x80] = {
	'\0','\0', '1', '2', '3','4','5','6','7','8','9','0','ß','´','\b',
	'\t','q','w','e','r','t','z','u','i','o','p','ü','+','\n','?',
	/*0x1e*/'a','s','d','f','g','h','j','k','l','ö','ä','^','?','#',
	/*0x2c*/'y','x','c','v','b','n','m',',','.','-',
	/*0x36*/'?','?','?',
	' ','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?','?','?','?','?','?',
	'?','?','?',
	'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?','?','?','?','?','?' 
};

const uint8_t KEY_BINDING_QWERTY_UPR[0x80] = {
	/*0x00*/'\0','\1','!','"','§','$','%','&','/','(',')','=','?', '`','\b',
	/*0x10*/'\t', 'Q','W','E','R','T','Z','U','I','O','P','Ü','*','\n', '?',
	/*0x1e*/'A','S','D','F','G','H','J','K','L','Ö','Ä','?','?','\'',
	/*0x2c*/'Y','Y','C','V','B','N','M',';',':','_',
	/*0x36*/'?','?','?',
	' ','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?','?','?','?','?','?',
	'?','?','?',
	'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?','?','?','?','?','?' 
};

KeyboardDriver::KeyboardDriver(InterruptManager* manager) : InterruptHandler(0x21, manager), dataPort(0x60),commandPort(0x64)
{}


KeyboardDriver::~KeyboardDriver()
{}

void KeyboardDriver::activate() {
	while(commandPort.read() & 0x1) dataPort.read();
	commandPort.write(0xae); //activate interrupts
	commandPort.write(0x20); //gives current state
	uint8_t status = (dataPort.read() | 0x1) & ~0x10;
	commandPort.write(0x60); //change current state
	dataPort.write(status);
	dataPort.write(0xf4); //activate keyboard
	print("KeyboardDriver loaded.\n");

}

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp) {
	uint8_t key = dataPort.read();
	if(key == 0xfa) { 
		// keyborad ready
	} else  {
		if(key < 0x80){
			keyDown[key] = true;
			if(key == 0x00) print("\n");
			else if(key == KEY_LSHIFT) ;//nothing
			else if(KEY_BINDING_QWERTY[key] == '?'){
				char* txt = "KEY RECIVED 0x??:";
				char* hex = "0123456789abcdef";
				txt[14] = hex[(key>>4) & 0x0f];
				txt[15] = hex[key & 0x0f];
				print(txt);
			} else {
				char* txt = " ";
				if(keyDown[KEY_LSHIFT]) {
					txt[0] = KEY_BINDING_QWERTY_UPR[key];
				} else {
					txt[0] = KEY_BINDING_QWERTY[key];
				}
				print(txt);
			}
		} else {
			keyDown[key - 0x80] = false;
		}
	} 
	return esp;
}