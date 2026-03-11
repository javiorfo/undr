#ifndef CASK_JWT_H
#define CASK_JWT_H

#include <stdint.h>
#include <stddef.h>
#include "cask/arena.h"

typedef struct {
    char *header;
    char *payload;
} Jwt;

Jwt decode_jwt(Arena *a, const char* jwt_str);

#endif
