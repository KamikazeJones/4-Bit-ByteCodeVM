#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stddef.h>
#include <stdint.h>
#include "dyn_bytearray.h"

/*
 * Public interface for the assembler module.
 * The assembler translates a textual program into the 4-bit bytecode.
 *
 * The caller provides the source as a NUL-terminated string and a pointer
 * to a dynamic byte array where the resulting bytes will be appended.
 * The function returns 0 on success or a negative error code on failure.
 */

/* opcode values correspond to the 4-bit nibble encoded in bytecode */
typedef enum {
    OPC_PS  = 0x0,  /* $ : push immediate byte */
    OPC_SL  = 0x1,  /* < : shift left (logical) */
    OPC_SR  = 0x2,  /* > : shift right (logical) */
    OPC_RD  = 0x3,  /* @ : read memory */
    OPC_WR  = 0x4,  /* ! : write memory */
    OPC_JZ  = 0x5,  /* ? : jump if zero */
    OPC_AD  = 0x6,  /* + : add with carry */
    OPC_DP  = 0x7,  /* = : duplicate top of stack */
    OPC_DR  = 0x8,  /* / : drop top of stack */
    OPC_AN  = 0x9,  /* & : bitwise AND */
    OPC_OR  = 0xA,  /* | : bitwise OR */
    OPC_XR  = 0xB,  /* # : bitwise XOR */
    OPC_CL  = 0xC,  /* * : call */
    OPC_RT  = 0xD,  /* ; : return */
    OPC_RSVD= 0xE,  /* - : reserved */
    OPC_HL  = 0xF   /* F : halt */
} opcode_t;

/* mnemonic descriptor used internally by assembler; exposed in header
   for tests if necessary */
typedef struct mnemonic {
    char mnem_2[3];   /* two-char mnemonic string, e.g. "AD" */
    char mnem_1;      /* single-symbol alternative, e.g. '+' or '\0' */
    opcode_t code;    /* corresponding opcode value */
} mnemonic_t;

/* Assemble text "src" into the bytecode buffer.  Returns 0 on success.
   On error the buffer may be left in an indeterminate state. */
int assemble(const char *src, dyn_bytearray_t *output);

#endif /* ASSEMBLER_H */
