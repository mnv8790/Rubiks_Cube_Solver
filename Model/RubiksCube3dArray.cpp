#include "RubiksCube.h"

#include <array>
#include <string>

class RubiksCube3dArray : public RubiksCube {
private:
    array<char, 54> toStickerArray() const {
        array<char, 54> stickers{};
        for (int face = 0; face < 6; face++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    stickers[flatIndex(static_cast<FACE>(face), row, col)] = cube[face][row][col];
                }
            }
        }
        return stickers;
    }

    void loadStickerArray(const array<char, 54> &stickers) {
        for (int face = 0; face < 6; face++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    cube[face][row][col] = stickers[flatIndex(static_cast<FACE>(face), row, col)];
                }
            }
        }
    }

    RubiksCube &doMove(MOVE move) {
        array<char, 54> stickers = toStickerArray();
        applyMoveToStickerArray(stickers, move);
        loadStickerArray(stickers);
        return *this;
    }

public:
    char cube[6][3][3]{};

    RubiksCube3dArray() {
        loadStickerArray(solvedStickerArray());
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        return getColorFromLetter(cube[static_cast<int>(face)][row][col]);
    }

    bool isSolved() const override {
        return isStickerArraySolved(toStickerArray());
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

    bool operator==(const RubiksCube3dArray &other) const {
        for (int face = 0; face < 6; face++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (cube[face][row][col] != other.cube[face][row][col]) return false;
                }
            }
        }
        return true;
    }
};

struct Hash3d {
    size_t operator()(const RubiksCube3dArray &cube) const {
        string key;
        key.reserve(54);
        for (int face = 0; face < 6; face++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) key += cube.cube[face][row][col];
            }
        }
        return hash<string>()(key);
    }
};
