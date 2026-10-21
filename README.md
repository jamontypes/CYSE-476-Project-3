# RSA Public-Key Encryption and Signature Lab

A C implementation of the core RSA operations (key derivation, encryption, decryption, signing, and signature verification) using OpenSSL's Big Number (`BIGNUM`) library.

## Overview

RSA is one of the earliest public-key cryptosystems and is still widely used for secure communication. It relies on two large primes to generate a public/private key pair, which can then be used for encryption, decryption, digital signature generation, and signature verification.

The numbers involved in RSA are typically 512+ bits, far larger than native C integer types can hold, so this project uses OpenSSL's `BIGNUM` API to perform arbitrary-precision arithmetic. Each task works through one essential step of RSA on actual numbers.

## Requirements

- Linux (developed for Ubuntu 20.04)
- `gcc`
- OpenSSL development libraries

```bash
sudo apt-get install build-essential libssl-dev
```

## Building

Each task is a standalone C file. Compile with the crypto library linked (`-lcrypto`; that's a lowercase "L", not the number 1):

```bash
gcc task1.c -o task1 -lcrypto
./task1
```

Repeat for `task2.c` through `task6.c`.

## BIGNUM API Reference

The main OpenSSL calls used in this project:

| Purpose | Function |
| --- | --- |
| Create a context for temporary values | `BN_CTX_new()` |
| Allocate a big number | `BN_new()` |
| Assign from a decimal / hex string | `BN_dec2bn()` / `BN_hex2bn()` |
| Random number / random prime | `BN_rand()` / `BN_generate_prime_ex()` |
| Add / subtract | `BN_add()` / `BN_sub()` |
| Multiply | `BN_mul()` |
| Modular multiply | `BN_mod_mul()` |
| Modular exponentiation | `BN_mod_exp()` |
| Modular inverse | `BN_mod_inverse()` |

Full documentation: <https://linux.die.net/man/3/bn>

A helper is used throughout to print big numbers:

```c
void printBN(char *msg, BIGNUM *a)
{
    char *number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}
```

## Tasks

### Task 1: Using Big Numbers (`task1.c`)

Initialize three `BIGNUM` variables and compute `a * b` and `(a^b mod n)`.

- `a`: random 256-bit prime
- `b`: decimal string `273489463796838501848592769467194369268`
- `n`: random 256-bit number

### Task 2: Deriving the Private Key (`task2.c`)

Given primes `p`, `q`, and `e` (hex), let `n = p * q`, with `(e, n)` as the public key. Compute the private key `d`.

```
p = F7E75FDC469067FFDC4E847C51F452DF
q = E85CED54AF57E53E092113E62F436F4F
e = 0D88C3
```

> `p` and `q` here are only 128 bits for simplicity. Real-world RSA requires primes of at least 512 bits.

### Task 3: Encrypting a Message (`task3.c`)

Encrypt the message `A top secret!` with the public key `(e, n)`. The ASCII string is first converted to hex, then loaded as a `BIGNUM` with `BN_hex2bn()`.

```bash
python3 -c 'print("A top secret!".encode("utf-8").hex())'
# 4120746f702073656372657421
```

```
n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5
e = 010001   (65537 in decimal)
```

### Task 4: Decrypting a Message (`task4.c`)

Using the same key pair as Task 3, decrypt the ciphertext below and convert the result back to ASCII.

```
C = 8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F
```

```bash
python3 -c 'print(bytes.fromhex("<hex output>").decode("utf-8"))'
```

### Task 5: Signing a Message (`task5.c`)

Using the same key pair as Task 3, sign the message `I owe you $2000.` directly (not its hash). Then change the message slightly (e.g., `$2000` to `$3000`), sign it again, and compare the two signatures.

### Task 6: Verifying a Signature (`task6.c`)

Bob receives the message `Launch a missile.` from Alice along with a signature. Verify whether the signature is valid using Alice's public key.

```
S = 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F
e = 010001
n = AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115
```

Then repeat verification with a corrupted signature in which the last byte changes from `2F` to `3F` (a single-bit change), and observe how verification behaves.

## Repository Structure

```
.
├── task1.c
├── task2.c
├── task3.c
├── task4.c
├── task5.c
├── task6.c
└── README.md
```

## Notes

- This is an educational implementation. Textbook RSA (no padding, tiny key sizes, signing the message directly instead of a hash) is **not secure** and should never be used in production. Use a vetted library with proper padding schemes such as OAEP and PSS.
- Always free `BIGNUM` and `BN_CTX` objects when finished (`BN_free()`, `BN_CTX_free()`).
