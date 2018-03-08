/*#include "interrupts.h"

void print(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[0x100];
//InterruptManager* InterruptManager::activeInterruptManager = 0;

void InterruptManager::setInterruptDescriptorTableEntry(
		uint8_t interruptNumber,
		uint16_t codeSegmentSelector,
		void (*handler)(),
		uint8_t desciptorPrivilegeLevel,
		uint8_t desciptorType){
	const uint8_t IDT_DESC_PRESENT = 0x80;

	interruptDescriptorTable[interruptNumber].handlerAdress_lwr = (uint32_t) handler & 0xffff;
	interruptDescriptorTable[interruptNumber].handlerAdress_upr = (((uint32_t) handler) >> 16) & 0xffff;
	interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelector;
	interruptDescriptorTable[interruptNumber].reserved = 0;
	interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | desciptorType | ((desciptorPrivilegeLevel & 3) << 5);
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
:picMasterCommand(0x20),
 picMasterData(0x21),
 picSlaveCommand(0xa0),
 picSlaveData(0xa1)
{
	uint16_t codeSegment = gdt -> getCodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xe;
	for(int i = 0; i < 0xff; i++) {
		//handlers[i] = 0;
		setInterruptDescriptorTableEntry(i, codeSegment, &ignoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}
	setInterruptDescriptorTableEntry(0x20, codeSegment, &handleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x21, codeSegment, &handleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	
	picMasterCommand.write(0x11);
	picSlaveCommand.write(0x11);
	// add offset to interrupts
	picMasterData.write(0x20);
	picSlaveData.write(0x28);
	//tells who is  master/slave
	picMasterData.write(0x04);
	picSlaveData.write(0x02);
	// ??
	picMasterData.write(0x01);
	picSlaveData.write(0x01);
	// ??
	picMasterData.write(0x00);
	picSlaveData.write(0x00);


	InterruptDescriptorTablePointer idt;
	idt.size = 0x100 * sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m" (idt));
}

InterruptManager::~InterruptManager() {
	//deactivate();
}

void InterruptManager::activate() {
	//if(activeInterruptManager != 0) activeInterruptManager->deactivate();
	//activeInterruptManager = this;
	asm("sti");
}*//*

void InterruptManager::deactivate() {
	if(activeInterruptManager == this) {
		asm("cli");
		activeInterruptManager = 0;
	}
}*//*

uint32_t InterruptManager::handleInterrupt(uint8_t interrupt, uint32_t esp) {
	//asm("jmp 0");
	/*if(activeInterruptManager != 0) {
		return activeInterruptManager->doHandleInterrupt(interrupt, esp);
	}*//*
	char* foo = "INTERRUPT 0x00";
    char* hex = "0123456789ABCDEF";

    foo[12] = hex[(interrupt >> 4) & 0xF];
    foo[13] = hex[interrupt & 0xF];
    print(foo);

    return esp;
}
*/
/*uint32_t InterruptManager::doHandleInterrupt(uint8_t interrupt, uint32_t esp) {
	if(interrupt == 0x20) print("TI "); // timer interrupt
	if(interrupt != 0x20) print("NTI "); // timer interrupt	
	/*if(handlers[interrupt] != 0) {
		esp = handlers[interrupt]->handleInterrupt(esp);
	} else {
		if(0) {;} else {
			char* txt = "UNHANDLED INTERRUPT 0x??..";
			char* hex = "0123456789abcdef";
			txt[22] = hex[(interrupt>>4) & 0x0f];
			txt[23] = hex[interrupt & 0x0f];
			print(txt);
		}
	}*//*
	if(0x20 <= interrupt && interrupt < 0x30) { //HW-INT
		picMasterCommand.write(0x20);
		if(0x28 <= interrupt) picSlaveCommand.write(0x20);
	}
	return esp;
}*/



/*	this->interruptNumber = interruptNumber;
	this->interruptManager = manager;
	manager->handlers[interruptNumber] = this;
}
InterruptHandler::~InterruptHandler() {
	if(interruptManager->handlers[interruptNumber] == this)	interruptManager->handlers[interruptNumber] = 0;
}

uint32_t InterruptHandler::handleInterrupt(uint32_t esp) {
	return esp;
}*/

#include "interrupts.h"

void print(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::setInterruptDescriptorTableEntry(
		uint8_t interruptNumber,
		uint16_t codeSegmentSelector,
		void (*handler)(),
		uint8_t desciptorPrivilegeLevel,
		uint8_t desciptorType){
	const uint8_t IDT_DESC_PRESENT = 0x80;

	interruptDescriptorTable[interruptNumber].handlerAdress_lwr = (uint32_t) handler & 0xffff;
	interruptDescriptorTable[interruptNumber].handlerAdress_upr = (((uint32_t) handler) >> 16) & 0xffff;
	interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelector;
	interruptDescriptorTable[interruptNumber].reserved = 0;
	interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | desciptorType | ((desciptorPrivilegeLevel & 3) << 5);
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
:picMasterCommand(0x20),
 picMasterData(0x21),
 picSlaveCommand(0xa0),
 picSlaveData(0xa1)
{
	uint16_t codeSegment = gdt -> getCodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xe;
	for(int i = 0; i < 0xff; i++) {
		setInterruptDescriptorTableEntry(i, codeSegment, &ignoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}
	setInterruptDescriptorTableEntry(0x20, codeSegment, &handleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x21, codeSegment, &handleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	
	picMasterCommand.write(0x11);
	picSlaveCommand.write(0x11);
	// add offset to interrupts
	picMasterData.write(0x20);
	picSlaveData.write(0x28);
	//tells who is  master/slave
	picMasterData.write(0x04);
	picSlaveData.write(0x02);
	// ??
	picMasterData.write(0x01);
	picSlaveData.write(0x01);
	// ??
	picMasterData.write(0x00);
	picSlaveData.write(0x00);


	InterruptDescriptorTablePointer idt;
	idt.size = 0x100 * sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m" (idt));
}

InterruptManager::~InterruptManager() {

}

void InterruptManager::activate() {
	asm("sti");
}

uint32_t InterruptManager::handleInterrupt(uint8_t interrupt, uint32_t esp) {
	print("INTERRUPT\n");
	return esp;
}
