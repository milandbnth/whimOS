#include "gdt.h"
#include "idt.h"
#include "irq.h" 

void serial_write(char c) {
    __asm__ volatile ("outb %0, %1" : : "a"(c), "Nd"(0x3F8));
}

void serial_print(const char *str) {
    while (*str) {
        serial_write(*str++);
    }
}

static void timer_handler(registers_t *regs) {
    (void)regs;
    serial_print("tick\n");
}

void kernel_main() {
    gdt_init();
    idt_init();
    irq_init();

    irq_register(0, timer_handler);

    __asm__ volatile ("sti");
    
    serial_print("Hello from WhimOS!\n");
    serial_print("WhimOS is alive!\n");
    while(1);
}