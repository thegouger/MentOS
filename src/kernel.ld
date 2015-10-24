ENTRY(loader)  /* entry label */             

SECTIONS {
    . = 0x00100000;          /* load code at 1MB because GRUB reserves the first 1MB */

    .text ALIGN (0x1000) :   /* align to 4KB (page size) */ 
    {
        *(.text)             /* text section */
    }

    .rodata ALIGN (0x1000) : /* align to 4KB (page size) */ 
    {
        *(.rodata*)          /* read only data */
    }

    .data ALIGN (0x1000) :   /* align to 4KB (page size) */ 
    {
        *(.data)             /* data sections */
    }

    .bss ALIGN (0x1000) :    /* align to 4KB (page size) */ 
    {
        *(COMMON)            /* bss and COMMON sections */
        *(.bss)              
    }
}
