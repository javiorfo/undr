#include "undr/arena.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arena *arena_init(size_t capacity) {
    Arena *a = malloc(sizeof(Arena));
    a->size = capacity;
    a->offset = 0;
    a->buffer = malloc(capacity);
    return a;
}

void *arena_alloc(Arena *a, size_t size) {
    size = (size + 7) & ~7;

    if (a->offset + size <= a->size) {
        void *ptr = &a->buffer[a->offset];
        a->offset += size;
        return ptr;
    }

    fprintf(
        stderr,
        "Arena exceeded memory: initilized in %lub and try to allocate %lub\n",
        a->size, size + a->offset);

    return NULL;
}

void arena_reset(Arena *a) { a->offset = 0; }

void arena_free(Arena *a) {
    free(a->buffer);
    free(a);
    a = NULL;
}
