AS_PARAMS = --32
LD_PARAMS = -melf_i386
GPP_PARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings

objects = interrupts.o driver.o interruptstubs.o port.o loader.o gdt.o kernel.o scr_text.o keyboard.o
OBJ_PATH = obj/
SRC_PATH = src/
INCLUDE_PATH = include/



%.o: %.cpp
	g++ $(GPP_PARAMS) -o $@ -c $<

%.o: %.s
	as $(AS_PARAMS) -o $@ -c $<

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/myOSkernel.bin
	echo '####################' >> iso/boot/grub/grub.cfg
	echo '# MYOS ENTRY START #' >> iso/boot/grub/grub.cfg
	echo '####################' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'set timeout=5' >> iso/boot/grub/grub.cfg
	echo 'menuentry "myOS 0.1" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/myOSkernel.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

kernel.bin: linker.ld $(objects)
	ld $(LD_PARAMS) -T $< -o $@ $(objects)

install: kernel.bin
	@echo "!WARNING YOU ARE INSATLLING AN OPERATION SYSTEM KERNEL!"
	sudo cp $< /boot/ThornsOSkernel.bin

vm: kernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "MYOS" &


.PHONY: clean
clean: 
	rm -f $(objects) kernel.bin kernel.iso
	rm -rf iso
