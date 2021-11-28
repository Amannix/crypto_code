#include <openssl/evp.h>
#include "util.h"

int
block_cipher(const EVP_CIPHER *cipher, uint8_t *in, size_t len, uint8_t *out, uint8_t *key, uint8_t *iv, int enc) {
    int outl, enlen = 0;

    EVP_CIPHER_CTX *cipher_ctx = NULL;

    enc = enc ? 1 : 0;
    if (!in || !key || !out)
        return EXIT_FAILURE;

    /* 1. Initialize CIPHER CTX */
    cipher_ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit_ex(cipher_ctx, cipher, NULL, key, iv, enc);

    /* 2. Update cipher data */
    EVP_CipherUpdate(cipher_ctx, out, &outl, in, len);
    enlen += outl;

    /* 3. Final cipher data */
    EVP_CipherFinal(cipher_ctx, out + outl, &outl);
    enlen += outl;

    /* 4. return cipher data */
    OPENSSL_hexdump(stdout, EVP_CIPHER_name((EVP_CIPHER *)cipher), out, enlen);
    EVP_CIPHER_CTX_free(cipher_ctx);
    return enlen;
}

int
main(void) {
    uint8_t out[1024];

    /* {EVP_<CIPHER_NAME>_<MODE>()} are defined in the "openssl/evp.h" */
    block_cipher(EVP_sm4_cbc(), "12345", 5, out, "321", "321", 1);
    block_cipher(EVP_aes_256_gcm(), "12345", 5, out, "321", "321", 1);

    return EXIT_SUCCESS;
}