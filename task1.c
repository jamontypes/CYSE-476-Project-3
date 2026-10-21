// sam juarez 4/16/26 cyse 476 lab 3
// task1.c
#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *res = BN_new();

    BN_generate_prime_ex(a, 256, 1, NULL, NULL, NULL);
    BN_dec2bn(&b, "273489463796838501848592769467194369268");
    BN_rand(n, 256, 0, 0);

    BN_mul(res, a, b, ctx);
    printBN("a * b =", res);

    BN_mod_exp(res, a, b, n, ctx);
    printBN("a^b mod n =", res);

    BN_free(a); BN_free(b);
    BN_free(n); BN_free(res); BN_CTX_free(ctx);
    return 0;
}
