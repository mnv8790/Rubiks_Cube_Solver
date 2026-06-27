#ifndef CORNERPATTERNDATABASE_H
#define CORNERPATTERNDATABASE_H

#include "../Model/RubiksCube.h"
#include "PatternDatabase.h"
#include "PermutationIndexer.h"

#include <array>
#include <cstdint>

using namespace std;

class CornerPatternDatabase : public PatternDatabase {
private:
    PermutationIndexer<8> indexer;

public:
    CornerPatternDatabase();
    explicit CornerPatternDatabase(uint8_t initialValue);

    uint32_t getDatabaseIndex(const RubiksCube &cube) const override;
};

#endif
