#include <openssl/evp.h>
#include "util.h"

unsigned int
block_digest(const EVP_MD *md, uint8_t *str, size_t slen, uint8_t *out) {
    unsigned int mdLen;
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    /* 1. Initialize CIPHER CTX */
    EVP_MD_CTX_init(mdctx);
    EVP_DigestInit_ex(mdctx, md, NULL);

    /* 2. Update digest data */
    EVP_DigestUpdate(mdctx, str, slen);

    /* 3. Final digest data */
    EVP_DigestFinal_ex(mdctx, out, &mdLen);

    /* 4. return digest data */
    OPENSSL_hexdump(stdout, EVP_MD_name((EVP_MD *)md), out, mdLen);
    EVP_MD_CTX_free(mdctx);
    return mdLen;
}

int
main(void) {
    uint8_t out[1024];

    /* {EVP_<DIGEST_NAME>_<MODE>()} are defined in the "openssl/evp.h" */
    block_digest(EVP_sha3_512(), "12345", 5, out);
    block_digest(EVP_sm3(), "12345", 5, out);
    return EXIT_SUCCESS;
}