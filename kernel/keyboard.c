// #include "keyboard.h"
// #include "irq.h"

// #define KEYBOARD_DATA_PORT 0x60

// extern void serial_print(const char *str);
// extern void serial_write(char c);

// static const char scancode_map[128] = {
//     0,   27, '1','2','3','4','5','6','7','8','9','0','-','=', 8,
//     '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
//     0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
//     0,  '\\','z','x','c','v','b','n','m',',','.','/', 0,
//     '*', 0,  ' '
// };

// static void keyboard_handler(registers_t *regs) {
//     (void)regs;
//     uint8_t scancode = inb(KEYBOARD_DATA_PORT);

//     // Bit 7 set = key release, ignore it
//     if (scancode & 0x80) return;

//     if (scancode < 128 && scancode_map[scancode]) {
//         char c = scancode_map[scancode];
//         serial_write(c);
//     }
// }

// void keyboard_init(void) {
//     irq_register(1, keyboard_handler);
// }