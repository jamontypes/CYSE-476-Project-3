// sam juarez 4/16/26 cyse 476 lab 3
// task5.c
#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *M1 = BN_new();
    BIGNUM *M2 = BN_new();
    BIGNUM *S1 = BN_new();
    BIGNUM *S2 = BN_new();

    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    //$2000 and $3000 hex respectively \/
    BN_hex2bn(&M1, "49206f776520796f752024323030302e");
    BN_hex2bn(&M2, "49206f776520796f752024333030302e");

    BN_mod_exp(S1, M1, d, n, ctx);
    BN_mod_exp(S2, M2, d, n, ctx);

    printBN("signature of $2000 = ", S1);
    printBN("signature of $3000 = ", S2);

    BN_free(n); BN_free(d); BN_free(M1); BN_free(M2);
    BN_free(S1); BN_free(S2); BN_CTX_free(ctx);
    return 0;
}
