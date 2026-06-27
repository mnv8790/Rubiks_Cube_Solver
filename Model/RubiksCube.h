#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class RubiksCube {
public:
    enum class FACE { UP, LEFT, FRONT, RIGHT, BACK, DOWN };
    enum class COLOR { WHITE, GREEN, RED, BLUE, ORANGE, YELLOW };

    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    struct StickerPlace {
        int x, y, z;
        int nx, ny, nz;
    };

    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;
    virtual bool isSolved() const = 0;

    static char getColorLetter(COLOR color);
    static COLOR getColorFromLetter(char color);
    static string getMove(MOVE move);

    void print() const;
    vector<MOVE> randomShuffleCube(unsigned int times);

    RubiksCube &move(MOVE move);
    RubiksCube &invert(MOVE move);

    virtual RubiksCube &f() = 0;
    virtual RubiksCube &fPrime() = 0;
    virtual RubiksCube &f2() = 0;
    virtual RubiksCube &u() = 0;
    virtual RubiksCube &uPrime() = 0;
    virtual RubiksCube &u2() = 0;
    virtual RubiksCube &l() = 0;
    virtual RubiksCube &lPrime() = 0;
    virtual RubiksCube &l2() = 0;
    virtual RubiksCube &r() = 0;
    virtual RubiksCube &rPrime() = 0;
    virtual RubiksCube &r2() = 0;
    virtual RubiksCube &d() = 0;
    virtual RubiksCube &dPrime() = 0;
    virtual RubiksCube &d2() = 0;
    virtual RubiksCube &b() = 0;
    virtual RubiksCube &bPrime() = 0;
    virtual RubiksCube &b2() = 0;

    string getCornerColorString(uint8_t index) const;
    uint8_t getCornerIndex(uint8_t index) const;
    uint8_t getCornerOrientation(uint8_t index) const;

    // Shared helper used by all three models. It keeps the move logic in one place.
    static array<char, 54> solvedStickerArray();
    static bool isStickerArraySolved(const array<char, 54> &stickers);
    static void applyMoveToStickerArray(array<char, 54> &stickers, MOVE move);

    static int flatIndex(FACE face, int row, int col);
    static StickerPlace placeFromFlatIndex(int index);
    static int flatIndexFromPlace(const StickerPlace &place);
};

#endif
