#include "dyn_bytearray.h"
#include <stdlib.h>

int dba_set_chunk(dyn_bytearray_t *buf, size_t chunk)
{
    if (chunk == 0)
        return -1;
    buf->chunk = chunk;
    return 0;
}

int dba_ensure(dyn_bytearray_t *buf, size_t needed)
{
    if (buf->size + needed <= buf->capacity)
        return 0;
    if (buf->chunk == 0)
        buf->chunk = 1;
    size_t newcap = buf->capacity;
    while (newcap < buf->size + needed)
        newcap += buf->chunk;
    uint8_t *p = realloc(buf->data, newcap);
    if (!p)
        return -1;
    buf->data = p;
    buf->capacity = newcap;
    return 0;
}

int dba_append(dyn_bytearray_t *buf, uint8_t b)
{
    if (dba_ensure(buf, 1) != 0)
        return -1;
    buf->data[buf->size++] = b;
    return 0;
}

void dba_free(dyn_bytearray_t *buf)
{
    free(buf->data);
    buf->data = NULL;
    buf->size = buf->capacity = 0;
}

int dba_init(dyn_bytearray_t *buf, size_t initial, size_t chunk)
{
    buf->data = malloc(initial);
    if (!buf->data)
        return -1;
    buf->size = 0;
    buf->capacity = initial;
    buf->chunk = chunk;
    return 0;
}
