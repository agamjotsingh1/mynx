OUTPUT_ARCH("riscv")
ENTRY(_start)
PHDRS { ram PT_LOAD; }
SECTIONS {
  . = 0x80000000;
  .text : { *(.text) } :ram
  .data : { *(.data) } :ram
  .bss  : { *(.bss) } :ram
  /DISCARD/ : { *(.note*) *(.comment) *(.riscv.attributes) }
}
