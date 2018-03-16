#define VERSION 0.1
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "driver.h"
#include "scr_text.h"
#include "keyboard.h"
//prints


//tatic uint8_t term_color = 0xff00;



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
    print("\n");
    
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(&gdt);
    print("Initializing Hardware, Stage 0\n");

    DriverManager driverManager;
    KeyboardDriver keyboardDriver(&interruptManager);
    driverManager.addDriver(&keyboardDriver);
    print("Initializing Hardware, Stage 1\n");
    driverManager.activateAll();

    print("Initializing Hardware, Stage 2\n");
    interruptManager.activate();

    //loadin done
    //while(1) {
    //	wait(100000);
    //	print(">");
    //}
    while(1);
}
