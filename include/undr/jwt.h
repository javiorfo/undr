#ifndef UNDR_JWT_H
#define UNDR_JWT_H

#include <stdint.h>
#include <stddef.h>
#include "undr/arena.h"

typedef struct {
    char *header;
    char *payload;
} Jwt;

Jwt decode_jwt(Arena *a, const char* jwt_str);

#endif
