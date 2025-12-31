#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../include/kem.h"   // Kyber 핵심 헤더
#include "../include/randombytes.h"

int main() {
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];    // 공개키
    uint8_t sk[CRYPTO_SECRETKEYBYTES];    // 개인키
    uint8_t ct[CRYPTO_CIPHERTEXTBYTES];   // 암호문
    uint8_t key_a[CRYPTO_BYTES];          // 앨리스가 만든 비밀키 (공유 비밀)
    uint8_t key_b[CRYPTO_BYTES];          // 밥이 복호화한 비밀키

    printf("[Kyber-512 KEM Test]\n");

    // 1. 키 생성 (KeyGen)
    printf("1. Generating Keypair... ");
    crypto_kem_keypair(pk, sk);
    printf("Done.\n");

    // 2. 캡슐화 (Encapsulation) - 암호화
    printf("2. Encapsulating... ");
    crypto_kem_enc(ct, key_a, pk); // key_a는 공유될 비밀키
    printf("Done.\n");

    // 3. 디캡슐화 (Decapsulation) - 복호화
    printf("3. Decapsulating... ");
    crypto_kem_dec(key_b, ct, sk); // key_b는 복호화된 비밀키
    printf("Done.\n");

    // 4. 검증 (Check)
    printf("4. Checking Shared Secret... ");
    if (memcmp(key_a, key_b, CRYPTO_BYTES) == 0) {
        printf("[SUCCESS] Keys match!\n");
        return 0;
    } else {
        printf("[FAILURE] Keys do not match.\n");
        return 1;
    }
}
