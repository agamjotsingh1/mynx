OUTPUT_ARCH("riscv")
ENTRY(_start)
PHDRS { ram PT_LOAD; }
SECTIONS {
  . = 0x80000000;
  .text : { 
    *(.text.init)
    *(.text*) 
  } :ram
  .data : { 
    *(.rodata*)
    *(.data*) 
    *(.sdata*)
  } :ram
  .bss  : { 
    *(.bss*) 
    *(.sbss*)
  } :ram
  /DISCARD/ : { *(.note*) *(.comment) *(.riscv.attributes) }
}