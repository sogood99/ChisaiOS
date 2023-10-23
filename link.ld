ENTRY(loader)                /* the name of the entry label */

SECTIONS {
    . = 0x00001000;          /* the code should be loaded at 0x1000 */

    .text :
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata :
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data :
    {
        *(.data)             /* all data sections from all files */
    }

    .bss :
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }

    /* extra stuff to fill for bootloader to have 15 sectors = 7680 bytes */
    .fill :
    {
        . = ALIGN(8);
        FILL(0xDEADC0DE);
        . = 0x00002000;
        BYTE(0xA);
    }
}
