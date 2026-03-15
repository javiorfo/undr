#ifndef UNDR_JWT_H
#define UNDR_JWT_H

#include <stdint.h>
#include <stddef.h>
#include "undr/arena.h"

/**
 * @brief Represents the decoded components of a JSON Web Token.
 * * Note: These are raw JSON strings, not parsed objects. 
 * They are null-terminated and allocated within the provided Arena.
 */
typedef struct {
    char *header;  /**< Decoded JSON header string. NULL if decoding failed. */
    char *payload; /**< Decoded JSON payload string. NULL if decoding failed. */
} Jwt;

/**
 * @brief Decodes a Base64URL encoded JWT string into its JSON components.
 * * This function performs Base64URL decoding on the header and payload segments.
 * It does NOT verify the signature or validate the JSON structure.
 * * @param a       Pointer to the Arena used for memory allocation.
 * @param jwt_str The null-terminated JWT string (header.payload.signature).
 * @return        A Jwt struct. On failure, header and/or payload will be NULL.
 * Memory is managed by the Arena and should not be manually freed.
 */
Jwt decode_jwt(Arena *a, const char* jwt_str);

#endif
