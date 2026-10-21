// sam juarez 4/16/26 cyse 476 lab 3
// task6.c
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
    BIGNUM *e = BN_new();
    BIGNUM *S = BN_new();
    BIGNUM *M_rec = BN_new();

    BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&S, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");

    BN_mod_exp(M_rec, S, e, n, ctx);
    printBN("recovered message hex = ", M_rec);

    BN_hex2bn(&S, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");
    BN_mod_exp(M_rec, S, e, n, ctx);
    printBN("recovered from corrupted signature = ", M_rec);

    BN_free(n); BN_free(e); BN_free(S); BN_free(M_rec); BN_CTX_free(ctx);
    return 0;
}
