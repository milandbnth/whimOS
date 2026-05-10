all:
	nasm -f elf32 boot/boot.asm -o boot/boot.o
	gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o
	ld -m elf_i386 -T linker.ld -o whimos.bin boot/boot.o kernel/kernel.o
run:
	qemu-system-x86_64 -kernel whimos.bin -display none -serial mon:stdio

clean:
	rm -f boot/boot.o kernel/kernel.o whimos.bin
