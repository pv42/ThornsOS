AS_PARAMS = --32
LD_PARAMS = -melf_i386
GPP_PARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fpermissive

objects = loader.o kernel.o

%.o: %.cpp
	g++ $(GPP_PARAMS) -o $@ -c $<

%.o: %.s
	as $(AS_PARAMS) -o $@ -c $<

clean: 
	rm -f *.o
	rm -f kernel.bin
	rm -f kernel.iso
	rm -rf iso

kernel.bin: linker.ld $(objects)
	ld $(LD_PARAMS) -T $< -o $@ $(objects)

install: kernel.bin
	echo "!WARNING YOU ARE INSATLLING AN OPERATION SYSTEM KERNEL!"
	sudo cp $< /boot/myOSkernel.bin

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/myOSkernel.bin
	echo '####################' >> iso/boot/grub/grub.cfg
	echo '# MYOS ENTRY START #' >> iso/boot/grub/grub.cfg
	echo '####################' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'set timeout=10' >> iso/boot/grub/grub.cfg
	echo 'menuentry "myOS 0.1" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/myOSkernel.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso