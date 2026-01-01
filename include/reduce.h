#ifndef REDUCE_H
#define REDUCE_H
#include <stdint.h>
#include "params.h"

#define QINV -3327 

// static inline을 붙여서 함수 호출 오버헤드 제거
static inline int16_t montgomery_reduce(int32_t a) {
    int16_t t;
    t = (int16_t)((int16_t)a * QINV);
    t = (a - (int32_t)t * KYBER_Q) >> 16;
    return t;
}

static inline int16_t barrett_reduce(int16_t a) {
    int16_t v;
    const int16_t v_val = ((1U << 26) + KYBER_Q / 2) / KYBER_Q;
    v = ((int32_t)v_val * a + (1 << 25)) >> 26;
    v *= KYBER_Q;
    return a - v;
}
#endif
