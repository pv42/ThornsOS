#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H 

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager;

class InterruptHandler {
protected:
	uint8_t interruptNumber;
	InterruptManager* interruptManager;
	InterruptHandler(uint8_t interruptNumber, InterruptManager* interruptManager);
	~InterruptHandler();
public:
	uint32_t handleInterrupt(uint32_t esp);
};

class InterruptManager {
friend class InterruptHandler;
protected:

	static InterruptManager* activeInterruptManager;
	InterruptHandler* handlers[0x100];
	struct GateDescriptor {
		uint16_t handlerAdress_lwr;
		uint16_t gdt_codeSegmentSelector;
		uint8_t reserved;
		uint8_t access;
		uint16_t handlerAdress_upr;
	} __attribute__((packed));

	static GateDescriptor interruptDescriptorTable[0x100];

	struct InterruptDescriptorTablePointer{
		uint16_t size;
		uint32_t base;
	}__attribute__((packed));

	static void setInterruptDescriptorTableEntry(
		uint8_t interrupt,
		uint16_t codeSegmentSelectorOffset,
		void (*handler)(),
		uint8_t desciptorPrivilegeLevel,
		uint8_t desciptorType
	);

	Port8Slow picMasterCommand;
	Port8Slow picMasterData;
	Port8Slow picSlaveCommand;
	Port8Slow picSlaveData;
public:
	InterruptManager(GlobalDescriptorTable* gdt); 
	~InterruptManager();
	void activate();
	void deactivate();
	static uint32_t handleInterrupt(uint8_t interrupt, uint32_t esp);
	uint32_t doHandleInterrupt(uint8_t interrupt, uint32_t esp);
	static void ignoreInterruptRequest();

	static void handleInterruptRequest0x00();
	static void handleInterruptRequest0x01();
};

#endif

