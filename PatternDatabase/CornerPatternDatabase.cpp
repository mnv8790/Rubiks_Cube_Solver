#include "CornerPatternDatabase.h"

CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(100179840) {}

CornerPatternDatabase::CornerPatternDatabase(uint8_t initialValue)
        : PatternDatabase(100179840, initialValue) {}

uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCube &cube) const {
    array<uint8_t, 8> cornerPermutation{};
    for (uint8_t i = 0; i < 8; i++) cornerPermutation[i] = cube.getCornerIndex(i);

    uint32_t permutationRank = indexer.rank(cornerPermutation);

    uint32_t orientationRank = 0;
    for (uint8_t i = 0; i < 7; i++) {
        orientationRank = orientationRank * 3 + cube.getCornerOrientation(i);
    }

    return permutationRank * 2187 + orientationRank;
}
