all: boot/boot.o boot/gdt_flush.o boot/idt_flush.o boot/isr.o boot/irq.o \
     kernel/kernel.o kernel/gdt.o kernel/idt.o kernel/irq.o
	ld -m elf_i386 -T linker.ld -o whimos.bin \
	    boot/boot.o boot/gdt_flush.o boot/idt_flush.o boot/isr.o boot/irq.o \
	    kernel/kernel.o kernel/gdt.o kernel/idt.o kernel/irq.o

boot/boot.o: boot/boot.asm
	nasm -f elf32 boot/boot.asm -o boot/boot.o

boot/gdt_flush.o: boot/gdt_flush.asm
	nasm -f elf32 boot/gdt_flush.asm -o boot/gdt_flush.o

boot/idt_flush.o: boot/idt_flush.asm
	nasm -f elf32 boot/idt_flush.asm -o boot/idt_flush.o

boot/isr.o: boot/isr.asm
	nasm -f elf32 boot/isr.asm -o boot/isr.o

boot/irq.o: boot/irq.asm
	nasm -f elf32 boot/irq.asm -o boot/irq.o

kernel/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

kernel/gdt.o: kernel/gdt.c
	gcc -m32 -ffreestanding -c kernel/gdt.c -o kernel/gdt.o

kernel/idt.o: kernel/idt.c
	gcc -m32 -ffreestanding -c kernel/idt.c -o kernel/idt.o

kernel/irq.o: kernel/irq.c
	gcc -m32 -ffreestanding -c kernel/irq.c -o kernel/irq.o

run:
	qemu-system-x86_64 -kernel whimos.bin -display none -serial mon:stdio

clean:
	rm -f boot/*.o kernel/*.o whimos.bin