.set IRQ_BASE, 0x20

.section .text

.extern _ZN16InterruptManager15handleInterruptEhj

.macro HandleException num
.global _ZN16InterruptManager16handleException\num\()Ev
_ZN16InterruptManager16handleException\num\()Ev:
	movb $\num, (interruptnumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26handleInterruptRequest\num\()Ev
_ZN16InterruptManager26handleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptnumber)
	jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:

	#save registers
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs


	#call c++ header
	pushl %esp
	push (interruptnumber)
	call _ZN16InterruptManager15handleInterruptEhj
	addl %esp, 6
	mov %eax, %esp

	#load registers
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa


.global _ZN16InterruptManager22ignoreInterruptRequestEv
_ZN16InterruptManager22ignoreInterruptRequestEv:
	iret

.data
	interruptnumber: .byte 0
