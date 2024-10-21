#include "types.h"

static uint64 seed = 1;

uint random(void) {
    seed = seed * 6364136223846793005ULL + 1;
    return (seed >> 32) & 0x7fffffff;
}

void srand(uint64 new_seed) {
    seed = new_seed;
}