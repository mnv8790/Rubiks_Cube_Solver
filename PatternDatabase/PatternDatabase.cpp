#include "PatternDatabase.h"

#include <fstream>
#include <stdexcept>

PatternDatabase::PatternDatabase() : database(1), tableSize(1), filledItems(0) {}

PatternDatabase::PatternDatabase(size_t size)
        : database(size, 0xFF), tableSize(size), filledItems(0) {}

PatternDatabase::PatternDatabase(size_t size, uint8_t initialValue)
        : database(size, initialValue), tableSize(size), filledItems(0) {}

bool PatternDatabase::setNumMoves(uint32_t index, uint8_t moves) {
    uint8_t oldValue = database.get(index);
    if (oldValue == 0x0F) filledItems++;

    if (moves < oldValue) {
        database.set(index, moves);
        return true;
    }
    return false;
}

bool PatternDatabase::setNumMoves(const RubiksCube &cube, uint8_t moves) {
    return setNumMoves(getDatabaseIndex(cube), moves);
}

uint8_t PatternDatabase::getNumMoves(uint32_t index) const {
    return database.get(index);
}

uint8_t PatternDatabase::getNumMoves(const RubiksCube &cube) const {
    return getNumMoves(getDatabaseIndex(cube));
}

size_t PatternDatabase::getSize() const { return tableSize; }
size_t PatternDatabase::getNumItems() const { return filledItems; }
bool PatternDatabase::isFull() const { return filledItems == tableSize; }

void PatternDatabase::toFile(const string &filePath) const {
    ofstream out(filePath, ios::binary | ios::trunc);
    if (!out) throw runtime_error("Could not write pattern database file");
    out.write(reinterpret_cast<const char *>(database.data()), database.storageSize());
}

bool PatternDatabase::fromFile(const string &filePath) {
    ifstream in(filePath, ios::binary | ios::ate);
    if (!in) return false;

    size_t fileSize = static_cast<size_t>(in.tellg());
    if (fileSize != database.storageSize()) return false;

    in.seekg(0, ios::beg);
    in.read(reinterpret_cast<char *>(database.data()), database.storageSize());
    filledItems = tableSize;
    return true;
}

vector<uint8_t> PatternDatabase::inflate() const {
    vector<uint8_t> out;
    database.inflate(out);
    return out;
}

void PatternDatabase::reset() {
    database.reset(0xFF);
    filledItems = 0;
}
