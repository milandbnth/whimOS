void serial_write(char c) {
    __asm__ volatile ("outb %0, %1" : : "a"(c), "Nd"(0x3F8));
}

void serial_print(const char *str) {
    while (*str) {
        serial_write(*str++);
    }
}

void kernel_main() {
    serial_print("Hello from WhimOS!\n");
    serial_print("WhimOS is alive!\n");
    while(1);
}
