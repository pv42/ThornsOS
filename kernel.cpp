void print(char* str) {
	unsigned short* DISPLAY_BUFFER = (unsigned short*) 0xb8000;
	for(int i = 0; str[i] != '\0'; i++) {
		DISPLAY_BUFFER[i] = (DISPLAY_BUFFER[i] & 0xff00) + str[i];
	}
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
	for(constructor* i = &start_ctors; i!= end_ctors; i++) {
		(*i)();
	}
}

extern "C" void init(void* mbs_info, unsigned int magic) {
	print("myOS 0.1 (c)pv42");
	while(1);
}