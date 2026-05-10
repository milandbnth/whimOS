global gdt_flush

gdt_flush:
    mov eax, [esp+4]   ; get the pointer passed from C
    lgdt [eax]         ; load it into the CPU

    mov ax, 0x10       ; 0x10 = index 2 (kernel data segment)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush    ; 0x08 = index 1 (kernel code segment)
                       ; far jump reloads CS
.flush:
    ret


section .note.GNU-stack noalloc noexec nowrite progbits