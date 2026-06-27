#ifndef CORNERDBMAKER_H
#define CORNERDBMAKER_H

#include "CornerPatternDatabase.h"
#include "../Model/RubiksCubeBitboard.cpp"

#include <cstdint>
#include <string>

using namespace std;

class CornerDBMaker {
private:
    string fileName;
    CornerPatternDatabase cornerDB;

public:
    explicit CornerDBMaker(string fileName);
    CornerDBMaker(string fileName, uint8_t initialValue);

    bool bfsAndStore();
};

#endif
