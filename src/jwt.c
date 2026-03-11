#include "undr/jwt.h"
#include "undr/arena.h"
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <string.h>

char *prepare_base64(Arena *a, const char *input, int length) {
    int padded_len = (length + 3) & ~3;
    char *buffer = arena_alloc(a, padded_len + 1);

    memcpy(buffer, input, length);

    for (int i = 0; i < length; i++) {
        if (buffer[i] == '-') buffer[i] = '+';
        if (buffer[i] == '_') buffer[i] = '/';
    }

    for (int i = length; i < padded_len; i++)
        buffer[i] = '=';

    buffer[padded_len] = '\0';
    return buffer;
}

Jwt decode_jwt(Arena *a, const char *jwt_str) {
    Jwt result = {NULL, NULL};
    const char *start = jwt_str;
    const char *dot;

    dot = strchr(start, '.');
    if (!dot) return result;

    int h_len = (int)(dot - start);
    char *h_b64 = prepare_base64(a, start, h_len);

    result.header = arena_alloc(a, h_len + 1);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO *bio = BIO_new_mem_buf(h_b64, -1);
    bio = BIO_push(b64, bio);
    int decoded_len = BIO_read(bio, result.header, h_len);
    result.header[decoded_len] = '\0';
    BIO_free_all(bio);

    // 2. Parse Payload
    start = dot + 1;
    dot = strchr(start, '.');
    if (!dot) return result;

    int p_len = (int)(dot - start);
    char *p_b64 = prepare_base64(a, start, p_len);

    result.payload = arena_alloc(a, p_len + 1);

    bio = BIO_push(BIO_new(BIO_f_base64()), BIO_new_mem_buf(p_b64, -1));
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    decoded_len = BIO_read(bio, result.payload, p_len);
    result.payload[decoded_len] = '\0';
    BIO_free_all(bio);

    return result;
}
