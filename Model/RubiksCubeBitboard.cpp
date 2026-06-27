#include "RubiksCube.h"

#include <array>
#include <cstdint>
#include <string>

class RubiksCubeBitboard : public RubiksCube {
private:
    static uint64_t encodeColor(char color) {
        switch (color) {
            case 'W': return 0;
            case 'G': return 1;
            case 'R': return 2;
            case 'B': return 3;
            case 'O': return 4;
            case 'Y': return 5;
            default: return 0;
        }
    }

    static char decodeColor(uint64_t code) {
        static const char colors[6] = {'W', 'G', 'R', 'B', 'O', 'Y'};
        return colors[code % 6];
    }

    array<char, 54> toStickerArray() const {
        array<char, 54> stickers{};
        for (int face = 0; face < 6; face++) {
            for (int cell = 0; cell < 9; cell++) {
                uint64_t code = (bitboard[face] >> (cell * 4)) & 0xFULL;
                stickers[face * 9 + cell] = decodeColor(code);
            }
        }
        return stickers;
    }

    void loadStickerArray(const array<char, 54> &stickers) {
        for (int face = 0; face < 6; face++) {
            bitboard[face] = 0;
            for (int cell = 0; cell < 9; cell++) {
                bitboard[face] |= encodeColor(stickers[face * 9 + cell]) << (cell * 4);
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
    uint64_t bitboard[6]{};

    RubiksCubeBitboard() {
        loadStickerArray(solvedStickerArray());
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int index = flatIndex(face, row, col);
        int faceIndex = index / 9;
        int cell = index % 9;
        uint64_t code = (bitboard[faceIndex] >> (cell * 4)) & 0xFULL;
        return getColorFromLetter(decodeColor(code));
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

    bool operator==(const RubiksCubeBitboard &other) const {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != other.bitboard[i]) return false;
        }
        return true;
    }
};

struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard &cube) const {
        size_t value = 0;
        for (uint64_t side: cube.bitboard) {
            value ^= hash<uint64_t>()(side + 0x9e3779b97f4a7c15ULL + (value << 6) + (value >> 2));
        }
        return value;
    }
};
