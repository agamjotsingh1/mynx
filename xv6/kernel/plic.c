#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

//
// the riscv Platform Level Interrupt Controller (PLIC).
//

void
plicinit(void)
{
}

void
plicinithart(void)
{
}

// ask the PLIC what interrupt we should serve.
int
plic_claim(void)
{
  int irq = *(uint32*)PLIC_IRQ;
  return irq;
}

// tell the PLIC we've served this IRQ.
void
plic_complete(int irq)
{
}
