/**
 * DCS2.Pilot STM32H743 application linker script
 *
 * Flash layout:
 *   0x08000000 - 0x0801FFFF : Bootloader (128KB)
 *   0x08020000 - 0x081FFFFF : Application (1920KB)
 *
 * SRAM layout:
 *   0x20000000 - 0x2001FFFF : DTCM (128KB)
 *   0x24000000 - 0x2407FFFF : AXI SRAM (512KB)
 *   0x30000000 - 0x3001FFFF : SRAM1+2 (128KB)
 *   0x38000000 - 0x3800FFFF : SRAM4 (64KB)
 */

MEMORY
{
    flash  (rx) : ORIGIN = 0x08020000, LENGTH = 1920K
    sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
    axiram (rwx) : ORIGIN = 0x24000000, LENGTH = 512K
    sram4  (rwx) : ORIGIN = 0x38000000, LENGTH = 64K
}

OUTPUT_ARCH(arm)
EXTERN(_vectors)
EXTERN(_bootdelay_signature)
ENTRY(__start)

SECTIONS
{
    .text :
    {
        _stext = ABSOLUTE(.);
        *(.vectors)
        . = ALIGN(8);
        /* app_descriptor_t located by make_can_boot_descriptor.py so the DroneCAN
         * bootloader can validate image crc/size (mirrors ark/can-rtk-gps) */
        KEEP(*(.app_descriptor))
        . = ALIGN(32);
        *(.text .text.*)
        *(.fixup)
        *(.gnu.warning)
        *(.rodata .rodata.*)
        *(.gnu.linkonce.t.*)
        *(.glue_7)
        *(.glue_7t)
        *(.got)
        *(.gcc_except_table)
        *(.gnu.linkonce.r.*)
        _etext = ABSOLUTE(.);
    } > flash

    .init_section :
    {
        _sinit = ABSOLUTE(.);
        KEEP(*(.init_array .init_array.*))
        _einit = ABSOLUTE(.);
    } > flash

    .ARM.extab :
    {
        *(.ARM.extab*)
    } > flash

    .ARM.exidx :
    {
        __exidx_start = ABSOLUTE(.);
        *(.ARM.exidx*)
        __exidx_end = ABSOLUTE(.);
    } > flash

    _eronly = ABSOLUTE(.);

    .data :
    {
        _sdata = ABSOLUTE(.);
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        CONSTRUCTORS
        _edata = ABSOLUTE(.);
    } > sram AT > flash

    .bss :
    {
        _sbss = ABSOLUTE(.);
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = ABSOLUTE(.);
    } > sram

    /* D3 power domain section — provides _sram4_heap_start for the 4th heap
     * region (CONFIG_MM_REGIONS=4). Mirrors boards/cubepilot/cubeorangeplus.
     */
    .sram4_reserve (NOLOAD) :
    {
        *(.sram4)
        . = ALIGN(4);
        _sram4_heap_start = ABSOLUTE(.);
    } > sram4

    /* Stabs debugging sections */
    .stab 0 : { *(.stab) }
    .stabstr 0 : { *(.stabstr) }
    .stab.excl 0 : { *(.stab.excl) }
    .stab.exclstr 0 : { *(.stab.exclstr) }
    .stab.index 0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment 0 : { *(.comment) }
    .debug_abbrev 0 : { *(.debug_abbrev) }
    .debug_info 0 : { *(.debug_info) }
    .debug_line 0 : { *(.debug_line) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_aranges 0 : { *(.debug_aranges) }
}
