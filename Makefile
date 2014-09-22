
CCOPTS := -Wall -O -ffreestanding -fomit-frame-pointer -nostdinc -fno-builtin -std=gnu99

kernel.bin: link.ld start.o main.o video.o memory.o io.o debug.o pci.o interrupts.o interrupt_stubs.o
	ld -T link.ld -o kernel.bin start.o main.o video.o memory.o io.o debug.o pci.o interrupts.o interrupt_stubs.o

main.o: main.c
	gcc $(CCOPTS) -c main.c -o main.o

video.o: video.c
	gcc $(CCOPTS) -c video.c -o video.o

memory.o: memory.c
	gcc $(CCOPTS) -c memory.c -o memory.o

io.o: io.c
	gcc $(CCOPTS) -c io.c -o io.o

pci.o: pci.c
	gcc $(CCOPTS) -c pci.c -o pci.o

debug.o: debug.c
	gcc $(CCOPTS) -c debug.c -o debug.o

interrupts.o: interrupts.c
	gcc $(CCOPTS) -c interrupts.c -o interrupts.o

start.o: start.s
	as start.s -o start.o

interrupt_stubs.o: interrupt_stubs.s
	as interrupt_stubs.s -o interrupt_stubs.o

iso: kernel.bin
	rm -rf boot.iso
	mkdir -p .iso/boot/grub
	cp kernel.bin .iso/kernel.bin
	cp grub.cfg .iso/boot/grub/grub.cfg
	grub-mkrescue -o boot.iso .iso

boot: iso
	qemu-system-i386 -cdrom boot.iso -serial stdio -net none -cpu pentium3 -d int,cpu_reset

debug: iso
	qemu-system-i386 -cdrom boot.iso -serial stdio -net none -cpu pentium3 -d int,cpu_reset -S -s
