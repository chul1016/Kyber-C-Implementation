#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h> // 시간 측정을 위한 헤더
#include "../include/kem.h"
#include "../include/randombytes.h"

#define ITERATIONS 10000 // 1만 번 반복

int main() {
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
    uint8_t key_a[CRYPTO_BYTES];
    uint8_t key_b[CRYPTO_BYTES];
    
    clock_t start, end;
    double cpu_time_used;

    printf("[Kyber-512 Benchmark] Running %d iterations...\n", ITERATIONS);

    // 1. KeyGen Benchmark
    start = clock();
    for(int i=0; i<ITERATIONS; i++) {
        crypto_kem_keypair(pk, sk);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("KeyGen: %.4f seconds (Avg: %.6f sec)\n", cpu_time_used, cpu_time_used/ITERATIONS);

    // 2. Encapsulation Benchmark
    start = clock();
    for(int i=0; i<ITERATIONS; i++) {
        crypto_kem_enc(ct, key_a, pk);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Encaps: %.4f seconds (Avg: %.6f sec)\n", cpu_time_used, cpu_time_used/ITERATIONS);

    // 3. Decapsulation Benchmark
    start = clock();
    for(int i=0; i<ITERATIONS; i++) {
        crypto_kem_dec(key_b, ct, sk);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Decaps: %.4f seconds (Avg: %.6f sec)\n", cpu_time_used, cpu_time_used/ITERATIONS);

    return 0;
}
