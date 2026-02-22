/*
 * assembler.c
 *
 * Simple framework for a 4‑Bit‑Bytecode assembler.
 *
 * The only thing we have for now is an enum describing the
 * 16 opcodes (one nibble each) recognized by the assembler.
 */

#include "assembler.h"

#include <stdint.h>
#include <ctype.h>
#include <string.h>

/*
 * Opcodes correspond to the nibble value stored in the bytecode.
 * High‑nibble goes first, low‑nibble follows.  The assembler will
 * eventually translate textual mnemonics into these values.
 */

/*
 * mnemonic descriptions used by the assembler parser.
 * - mnem_2: two-character alphanumeric mnemonic (zero-terminated)
 * - mnem_1: single character opcode (or '\0' if not used)
 * - code:   corresponding enum value (0x0..0xF)
 */


/* table mapping textual mnemonics to opcode values */
static const mnemonic_t mnemonic_table[] = {
    {"PS", '$', OPC_PS},
    {"SL", '<', OPC_SL},
    {"SR", '>', OPC_SR},
    {"RD", '@', OPC_RD},
    {"WR", '!', OPC_WR},
    {"JZ", '?', OPC_JZ},
    {"AD", '+', OPC_AD},
    {"DP", '=', OPC_DP},
    {"DR", '/', OPC_DR},
    {"AN", '&', OPC_AN},
    {"OR", '|', OPC_OR},
    {"XR", '#', OPC_XR},
    {"CL", '*', OPC_CL},
    {"RT", ';', OPC_RT},
    {"RS", '-', OPC_RSVD},
    {"HL", '.', OPC_HL}
};

/* stub implementation only */
int assemble(const char *src, dyn_bytearray_t *output)
{
    if (!src || !output)
        return -1;
    (void)src;
    (void)output;
    return 0;
}

#include "dyn_bytearray.h"

/*
 * assembler entry point (currently stub):
 * simply returns error if source is NULL, otherwise 0.
 * Real implementation will parse tokens, lookup mnemonics, and emit
 * bytes into the output buffer using dyn_bytearray helpers.
 */

/* convert single hex digit to value, -1 if invalid */
static int hexval(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

/* lookup mnemonic starting at s; returns length in *len and opcode in *code;
   returns 0 on success, -1 if unknown */
static int lookup_opcode(const char *s, int *len, uint8_t *code)
{
    /* try two-letter mnemonic first */
    if (s[0] && s[1] && isalnum((unsigned char)s[0]) && isalnum((unsigned char)s[1])) {
        char tmp[3] = { s[0], s[1], '\0' };
        for (size_t i = 0; i < sizeof(mnemonic_table)/sizeof(mnemonic_table[0]); ++i) {
            if (mnemonic_table[i].mnem_2[0] &&
                strcmp(tmp, mnemonic_table[i].mnem_2) == 0) {
                *len = 2;
                *code = mnemonic_table[i].code;
                return 0;
            }
        }
    }
    /* try single-character form */
    for (size_t i = 0; i < sizeof(mnemonic_table)/sizeof(mnemonic_table[0]); ++i) {
        if (mnemonic_table[i].mnem_1 && s[0] == mnemonic_table[i].mnem_1) {
            *len = 1;
            *code = mnemonic_table[i].code;
            return 0;
        }
    }
    return -1;
}

int assemble(const char *src, dyn_bytearray_t *output)
{
    if (!src || !output)
        return -1;

    uint8_t half = 0;
    int have_half = 0;

    while (*src) {
        if (isspace((unsigned char)*src)) {
            ++src;
            continue;
        }

        if (*src == '$') {
            /* push immediate opcode */
            if (have_half) {
                /* flush previous nibble with zero low */
                if (dba_append(output, half) != 0)
                    return -1;
                have_half = 0;
            }
            uint8_t opcode = OPC_PS;
            /* append nibble directly as full byte to simplify */
            if (dba_append(output, opcode) != 0)
                return -1;
            ++src;
            int hi = hexval(*src++);
            if (hi < 0) return -1;
            int lo = hexval(*src++);
            if (lo < 0) return -1;
            uint8_t imm = (hi << 4) | lo;
            if (dba_append(output, imm) != 0)
                return -1;
            continue;
        }

        int len;
        uint8_t code;
        if (lookup_opcode(src, &len, &code) != 0)
            return -1;

        /* pack nibble into byte */
        if (!have_half) {
            half = (uint8_t)(code << 4);
            have_half = 1;
        } else {
            half |= (uint8_t)code;
            if (dba_append(output, half) != 0)
                return -1;
            have_half = 0;
        }
        src += len;
    }

    if (have_half) {
        /* pad low nibble with zero */
        if (dba_append(output, half) != 0)
            return -1;
        have_half = 0;
    }
    return 0;
}

/* future assembler code will go here */
