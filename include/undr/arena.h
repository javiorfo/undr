#ifndef UNDR_ARENA_H
#define UNDR_ARENA_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief A region-based linear allocator (Arena).
 * * Provides fast, contiguous memory allocation. Memory is allocated by 
 * "bumping" an offset pointer and can only be freed all at once.
 */
typedef struct {
    size_t size;      /**< Total capacity of the arena in bytes. */
    size_t offset;    /**< Current position for the next allocation. */
    uint8_t *buffer;  /**< Pointer to the start of the memory block. */
} Arena;

/**
 * @brief Initializes a new arena with a fixed capacity.
 * @param capacity The total number of bytes to reserve.
 * @return A pointer to the initialized Arena, or NULL if heap allocation fails.
 */
Arena *arena_init(size_t capacity);

/**
 * @brief Allocates a block of memory from the arena.
 * @param a    The arena to allocate from.
 * @param size The number of bytes needed.
 * @return A pointer to the allocated block, or NULL if the arena is full.
 * @note This does NOT align memory. For production, consider adding alignment logic.
 */
void *arena_alloc(Arena *a, size_t size);

/**
 * @brief Resets the arena offset to zero.
 * * This effectively "frees" all previous allocations, making the entire 
 * capacity available again without releasing the underlying buffer.
 */
void arena_reset(Arena *a);

/**
 * @brief Fully deallocates the arena and its underlying buffer.
 * * Use this only when the arena is no longer needed. All pointers 
 * returned by arena_alloc() become invalid after this call.
 */
void arena_free(Arena *a);

#endif
