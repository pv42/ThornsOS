#include "scr_text.h"
#include "types.h"

void clrScrn() {
    static uint16_t* Video_Memory = (uint16_t*) 0xb8000;
    for(int y = 0; y < 25; y++) {
        for(int x = 0; x < 80; x++) {
            Video_Memory[80*y + x] = (Video_Memory[80*y + x] & 0xff00) | ' ';
        }
    }
}

void dec_str(int number, char* target, int size) {
    for(int i = 0; number!=0 && i <= size; i++) {
        target[size-i] = '0' + number%10;
        number/=10;
    }
}

void hex_str(int number, char* target, int size) {
    char* hex = "0123456789abcdef";
    for(int i = 0; number!=0 && i <= size; i++) {
        target[size-i] = '0' + number&0xf;
        number/=16;
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
        //display is limited to 80x25
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