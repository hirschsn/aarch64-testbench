
#include <cassert>
#include <cstdio>
#include <cinttypes>
#include <arm_neon.h>

void axpy(int n, float a, float *__restrict x, float *__restrict y)
{
    assert(n % 4 == 0);
    assert(((uintptr_t) x % 4) == 0);
    assert(((uintptr_t) y % 4) == 0);

    const float32x4_t ai = vdupq_n_f32(a);
    for (int i = 0; i <= n; i += 4) {               // Maybe a bug here?
        const float32x4_t xi = vld1q_f32(x + i);
        const float32x4_t yi = vld1q_f32(y + i);
        const float32x4_t zi = vfmaq_f32(yi, xi, ai);
        vst1q_f32(y + i, zi);
    }
}

int main()
{
    float xs[] = {0.0F, 1.0F, 2.0F, 3.0F};
    float ys[] = {-1.0F, 2.0F, -2.0F, 0.0F};

    axpy(4, 1.0F, xs, ys);

    assert(ys[0] == -1.0F);
    assert(ys[1] == 3.0F);
    assert(ys[2] == 0.0F);
    assert(ys[3] == 30.0F);               // Maybe a bug here?
}
