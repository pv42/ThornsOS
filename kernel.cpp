#define VERSION 0.1
#include "types.h"
#include "gdt.h"
#include "port.h"
#include "interrupts.h"

//prints


//tatic uint8_t term_color = 0xff00;
void clrScrn() {
    static uint16_t* Video_Memory = (uint16_t*) 0xb8000;
    for(int y = 0; y < 25; y++) {
        for(int x = 0; x < 80; x++) {
            Video_Memory[80*y + x] = (Video_Memory[80*y + x] & 0xff00) | ' ';
        }
    }
}

void print(char* str) {
    static uint16_t* Video_Memory = (uint16_t*) 0xb8000;
    static uint8_t x=0, y=0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\n') {
            y++;
            x = 0;
        } else if(str[i] == '\r'){ 
        	x = 0;
        } else if(str[i] == '\b'){ 
        	x--;
        	if(x < 0) x = 0;
        } else {
        	uint16_t color;
        	color = Video_Memory[80*y + x] & 0xff00;
            //color = term_color;
            Video_Memory[80*y + x] = color | (str[i]);
            x++;
        }
        if(x >= 80) {
            x = 0;
            y++;
            if(y >= 25) {
                x=0;
                y=0;
                clrScrn();
            }
        }
    }
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

void wait(int c) { //nopnopnopnopnonpnnonpnonpnon
	for(int i = 0; i < c * 1000; i++) __asm__ volatile("nop");
}

extern "C" void init(void* mbs_info, uint32_t mb_magic) {
    //callConstructors();
    print("ThornsOS Version 0.1 \n");
    print("\n");
    print("(c) pv42\n");
    
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(&gdt);
    //hm inits
    interruptManager.activate();


    //loadin done
    wait(100000);
        print(">");
    
    while(1);
}
