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
