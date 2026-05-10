all: boot/boot.o boot/gdt_flush.o kernel/kernel.o kernel/gdt.o
	ld -m elf_i386 -T linker.ld -o whimos.bin boot/boot.o boot/gdt_flush.o kernel/kernel.o kernel/gdt.o

boot/boot.o: boot/boot.asm
	nasm -f elf32 boot/boot.asm -o boot/boot.o

boot/gdt_flush.o: boot/gdt_flush.asm
	nasm -f elf32 boot/gdt_flush.asm -o boot/gdt_flush.o

kernel/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

kernel/gdt.o: kernel/gdt.c
	gcc -m32 -ffreestanding -c kernel/gdt.c -o kernel/gdt.o

run:
	qemu-system-x86_64 -kernel whimos.bin -display none -serial mon:stdio

clean:
	rm -f boot/*.o kernel/*.o whimos.bin
