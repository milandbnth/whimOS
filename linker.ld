ENTRY(start)

PHDRS {
    text PT_LOAD FLAGS(5);   /* R + X = 101 in binary = 5 */
    data PT_LOAD FLAGS(6);   /* R + W = 110 in binary = 6 */
}

SECTIONS {
    . = 0x100000;

    .multiboot : { *(.multiboot) } :text
    .text      : { *(.text)      } :text
    .rodata    : { *(.rodata)    } :text

    .data      : { *(.data)      } :data
    .bss       : { *(.bss)       } :data
}
