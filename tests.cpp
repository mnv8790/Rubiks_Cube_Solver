#include "Model/RubiksCube3dArray.cpp"
#include "Model/RubicsCube1dArray.cpp"
#include "Model/RubiksCubeBitboard.cpp"
#include "Solver/IDDFSSolver.h"
#include "PatternDatabase/NibbleArray.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int passed = 0;
static int failed = 0;

static void check(bool condition, const string &name) {
    if (condition) {
        cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        cout << "[FAIL] " << name << "\n";
        failed++;
    }
}

template<typename CubeType>
static void testMoveInverse(const string &modelName) {
    for (int i = 0; i < 18; i++) {
        CubeType cube;
        CubeType solved;
        auto move = static_cast<RubiksCube::MOVE>(i);

        cube.move(move);
        cube.invert(move);

        check(cube == solved, modelName + " move followed by inverse: " + RubiksCube::getMove(move));
    }
}

template<typename CubeType>
static void testFourTurnsRestore(const string &modelName) {
    vector<RubiksCube::MOVE> faceMoves = {
        RubiksCube::MOVE::L,
        RubiksCube::MOVE::R,
        RubiksCube::MOVE::U,
        RubiksCube::MOVE::D,
        RubiksCube::MOVE::F,
        RubiksCube::MOVE::B
    };

    for (auto move: faceMoves) {
        CubeType cube;
        CubeType solved;

        for (int turn = 0; turn < 4; turn++) cube.move(move);

        check(cube == solved, modelName + " four turns restore: " + RubiksCube::getMove(move));
    }
}

static void testShortSolve() {
    RubiksCubeBitboard cube;
    cube.move(RubiksCube::MOVE::R);
    cube.move(RubiksCube::MOVE::U);
    cube.move(RubiksCube::MOVE::FPRIME);

    IDDFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, 5);
    vector<RubiksCube::MOVE> solution = solver.solve();

    check(solver.rubiksCube.isSolved(), "IDDFS solves a 3-move scramble");
    check(!solution.empty(), "IDDFS returns solution moves");
}

static void testNibbleArray() {
    NibbleArray values(6);
    values.set(0, 3);
    values.set(1, 12);
    values.set(4, 7);

    check(values.get(0) == 3, "NibbleArray stores even index");
    check(values.get(1) == 12, "NibbleArray stores odd index");
    check(values.get(4) == 7, "NibbleArray stores later index");
}

int main() {
    cout << "Rubik's Cube Solver Tests\n";

    testMoveInverse<RubiksCube3dArray>("3D array");
    testMoveInverse<RubiksCube1dArray>("1D array");
    testMoveInverse<RubiksCubeBitboard>("Bitboard");

    testFourTurnsRestore<RubiksCube3dArray>("3D array");
    testFourTurnsRestore<RubiksCube1dArray>("1D array");
    testFourTurnsRestore<RubiksCubeBitboard>("Bitboard");

    testShortSolve();
    testNibbleArray();

    cout << "\nPassed: " << passed << "  Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
