.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<< 1)
.set CHECK, -(MAGIC + FLAGS)

.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECK 

.section .text
.extern init
.extern callConstructors
.global loader

loader:
	mov $kernel_stack, %esp
	#call callConstructors needed for some c++ constructors but crashes virtbox
	push %eax
	push %ebx
	call init

_stop:
	cli
	hlt
	jmp _stop

.section .bss
.space 4*1024*1024 # 4 MiB 
kernel_stack:
