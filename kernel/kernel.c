#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "shell.h" 
// #include "keyboard.h"


void serial_write(char c) {
    __asm__ volatile ("outb %0, %1" : : "a"(c), "Nd"(0x3F8));
}

void serial_print(const char *str) {
    while (*str) {
        serial_write(*str++);
    }
}

// static void timer_handler(registers_t *regs) {
//     (void)regs;
//     // serial_print("tick\n");
// }

char serial_read(void) {
    while (!(inb(0x3FD) & 1));  // wait until data ready
    return inb(0x3F8);
}

void kernel_main() {
    gdt_init();
    idt_init();
    irq_init();

    // irq_register(0, timer_handler);
    // keyboard_init();

    __asm__ volatile ("sti");

    shell_init();
    
    // serial_print("Hello from WhimOS!\n");
    // serial_print("WhimOS is alive!\n");
    // serial_print("Type something:\n");
    while(1) {

        shell_run();    
    }
}