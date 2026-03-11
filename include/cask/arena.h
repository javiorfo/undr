#ifndef CASK_ARENA_H
#define CASK_ARENA_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    size_t size;
    size_t offset;
    uint8_t *buffer;
} Arena;

Arena *arena_init(size_t capacity);
void *arena_alloc(Arena *a, size_t size);
void arena_reset(Arena *a);
void arena_free(Arena *a);

#endif
