#ifndef DYN_BYTEARRAY_H
#define DYN_BYTEARRAY_H

#include <stddef.h>
#include <stdint.h>

/* dynamic byte buffer used by assembler and potentially others */

typedef struct dyn_bytearray {
    uint8_t *data;
    size_t size;
    size_t capacity;
    size_t chunk;      /* amount to grow when expanding */
} dyn_bytearray_t;

/* basic operations on a buffer */
int dba_init(dyn_bytearray_t *buf, size_t initial, size_t chunk);
int dba_set_chunk(dyn_bytearray_t *buf, size_t chunk);
int dba_ensure(dyn_bytearray_t *buf, size_t needed);
int dba_append(dyn_bytearray_t *buf, uint8_t b);
void dba_free(dyn_bytearray_t *buf);

#endif /* DYN_BYTEARRAY_H */
