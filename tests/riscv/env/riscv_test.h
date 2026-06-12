#ifndef _ENV_MYNX_RISCV_TEST_H
#define _ENV_MYNX_RISCV_TEST_H

#define RVTEST_RV64U
#define RVTEST_RV32U

#define TESTNUM x28

#define RVTEST_CODE_BEGIN \
  .text; \
  .global _start; \
  _start:

#define RVTEST_CODE_END

// both are same as spike will do the major checking work
#define RVTEST_PASS \
  1: j 1b;

#define RVTEST_FAIL \
  1: j 1b;

#define RVTEST_DATA_BEGIN .data;

#define RVTEST_DATA_END

#endif