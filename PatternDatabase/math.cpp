#include "math.h"

uint32_t factorial(uint32_t value) {
    uint32_t result = 1;
    for (uint32_t i = 2; i <= value; i++) result *= i;
    return result;
}

uint32_t pick(uint32_t total, uint32_t choose) {
    uint32_t result = 1;
    for (uint32_t i = 0; i < choose; i++) result *= (total - i);
    return result;
}
