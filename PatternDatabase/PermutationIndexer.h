#ifndef PERMUTATIONINDEXER_H
#define PERMUTATIONINDEXER_H

#include "math.h"

#include <array>
#include <bitset>
#include <cstdint>

using namespace std;

template<size_t N, size_t K = N>
class PermutationIndexer {
private:
    array<uint32_t, (1 << N)> onesBefore{};
    array<uint32_t, K> placeValues{};

public:
    PermutationIndexer() {
        for (uint32_t mask = 0; mask < (1 << N); mask++) {
            onesBefore[mask] = bitset<N>(mask).count();
        }

        for (uint32_t i = 0; i < K; i++) {
            placeValues[i] = pick(N - 1 - i, K - 1 - i);
        }
    }

    uint32_t rank(const array<uint8_t, K> &items) const {
        bitset<N> used;
        uint32_t answer = 0;

        for (uint32_t i = 0; i < K; i++) {
            uint8_t value = items[i];
            uint32_t smallerUsed = 0;
            for (uint8_t candidate = 0; candidate < value; candidate++) {
                if (used[N - 1 - candidate]) smallerUsed++;
            }

            answer += (value - smallerUsed) * placeValues[i];
            used[N - 1 - value] = 1;
        }
        return answer;
    }
};

#endif
