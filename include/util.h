
#ifndef HEADER_UTIL_H
#define HEADER_UTIL_H
#include <stdint.h>
#include <stddef.h>

__always_inline void
OPENSSL_hexdump(FILE *stream, const char *title, uint8_t *buff, size_t len) {
    char *outhex, *p;
    p = buff;
    fprintf(stream, "[%s]:\n", title);

    while (len > 16) {
        outhex = OPENSSL_buf2hexstr(p, 16);
        fprintf(stream, "%s\n", outhex);
        OPENSSL_free(outhex);
        len -= 16;
        p += 16;
    }

    outhex = OPENSSL_buf2hexstr(p, len);
    fprintf(stream, "%s\n\n", outhex);
    OPENSSL_free(outhex);
}

#endif