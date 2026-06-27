#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

#include "../Model/RubiksCube.h"
#include "NibbleArray.h"

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class PatternDatabase {
private:
    NibbleArray database;
    size_t tableSize;
    size_t filledItems;

protected:
    PatternDatabase();

public:
    explicit PatternDatabase(size_t size);
    PatternDatabase(size_t size, uint8_t initialValue);

    virtual uint32_t getDatabaseIndex(const RubiksCube &cube) const = 0;

    bool setNumMoves(uint32_t index, uint8_t moves);
    bool setNumMoves(const RubiksCube &cube, uint8_t moves);

    uint8_t getNumMoves(uint32_t index) const;
    uint8_t getNumMoves(const RubiksCube &cube) const;

    size_t getSize() const;
    size_t getNumItems() const;
    bool isFull() const;

    void toFile(const string &filePath) const;
    bool fromFile(const string &filePath);

    vector<uint8_t> inflate() const;
    void reset();
};

#endif
