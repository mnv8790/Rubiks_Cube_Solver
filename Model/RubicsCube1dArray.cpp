#include "RubiksCube.h"

#include <array>
#include <string>

class RubiksCube1dArray : public RubiksCube {
private:
    RubiksCube &doMove(MOVE move) {
        applyMoveToStickerArray(cube, move);
        return *this;
    }

public:
    array<char, 54> cube{};

    RubiksCube1dArray() {
        cube = solvedStickerArray();
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        return getColorFromLetter(cube[flatIndex(face, row, col)]);
    }

    bool isSolved() const override {
        return isStickerArraySolved(cube);
    }

    RubiksCube &f() override { return doMove(MOVE::F); }
    RubiksCube &fPrime() override { return doMove(MOVE::FPRIME); }
    RubiksCube &f2() override { return doMove(MOVE::F2); }
    RubiksCube &u() override { return doMove(MOVE::U); }
    RubiksCube &uPrime() override { return doMove(MOVE::UPRIME); }
    RubiksCube &u2() override { return doMove(MOVE::U2); }
    RubiksCube &l() override { return doMove(MOVE::L); }
    RubiksCube &lPrime() override { return doMove(MOVE::LPRIME); }
    RubiksCube &l2() override { return doMove(MOVE::L2); }
    RubiksCube &r() override { return doMove(MOVE::R); }
    RubiksCube &rPrime() override { return doMove(MOVE::RPRIME); }
    RubiksCube &r2() override { return doMove(MOVE::R2); }
    RubiksCube &d() override { return doMove(MOVE::D); }
    RubiksCube &dPrime() override { return doMove(MOVE::DPRIME); }
    RubiksCube &d2() override { return doMove(MOVE::D2); }
    RubiksCube &b() override { return doMove(MOVE::B); }
    RubiksCube &bPrime() override { return doMove(MOVE::BPRIME); }
    RubiksCube &b2() override { return doMove(MOVE::B2); }

    bool operator==(const RubiksCube1dArray &other) const {
        return cube == other.cube;
    }
};

struct Hash1d {
    size_t operator()(const RubiksCube1dArray &cube) const {
        string key(cube.cube.begin(), cube.cube.end());
        return hash<string>()(key);
    }
};
