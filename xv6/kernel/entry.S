	# qemu -kernel loads the kernel at 0x80000000
        # and causes each CPU to jump there.
        # kernel.ld causes the following code to
        # be placed at 0x80000000.
.section .text
_entry:
        # clear BSS section
        la a0, sbss
        la a1, ebss
1:      bge a0, a1, 2f
        sd zero, 0(a0)
        addi a0, a0, 8
        j 1b
2:
	# set up a stack for C.
        # stack0 is declared in start.c,
        # with a 4096-byte stack per CPU.
        # sp = stack0 + (hartid * 4096)
        la sp, stack0
        li a0, 1024*4
        # not needed (single core)
	# csrr a1, mhartid
        # addi a1, a1, 1
        # mul a0, a0, a1
        add sp, sp, a0
	# jump to start() in start.c
        call start
spin:
        j spin
