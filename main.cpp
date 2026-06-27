#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Model/RubiksCubeBitboard.cpp"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"

using namespace std;
using namespace std::chrono;

static bool parseMove(const string &text, RubiksCube::MOVE &move) {
    for (int i = 0; i < 18; i++) {
        RubiksCube::MOVE candidate = static_cast<RubiksCube::MOVE>(i);
        if (RubiksCube::getMove(candidate) == text) {
            move = candidate;
            return true;
        }
    }
    return false;
}

static void printMoves(const vector<RubiksCube::MOVE> &moves) {
    if (moves.empty()) {
        cout << "(none)";
        return;
    }

    for (RubiksCube::MOVE move: moves) cout << RubiksCube::getMove(move) << ' ';
}

static void waitBeforeClosing(bool shouldWait) {
    if (!shouldWait) return;

    cout << "\nPress Enter to close...";
    string ignored;
    getline(cin, ignored);
}

int main(int argc, char *argv[]) {
    bool launchedWithoutArguments = argc == 1;
    RubiksCubeBitboard cube;
    vector<RubiksCube::MOVE> scramble;
    string databaseFile;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--db" && i + 1 < argc) {
            databaseFile = argv[++i];
            continue;
        }

        RubiksCube::MOVE move;
        if (!parseMove(arg, move)) {
            cout << "Invalid move: " << arg << "\n";
            cout << "Example: rubiks_solver R U F'\n";
            cout << "IDA*:   rubiks_solver --db Check_these/Database.txt R U F'\n";
            waitBeforeClosing(launchedWithoutArguments);
            return 1;
        }
        scramble.push_back(move);
    }

    if (scramble.empty()) {
        scramble = {RubiksCube::MOVE::R, RubiksCube::MOVE::U, RubiksCube::MOVE::FPRIME};
    }

    cout << "Scramble: ";
    printMoves(scramble);
    cout << "\n";

    for (RubiksCube::MOVE move: scramble) cube.move(move);
    cube.print();

    vector<RubiksCube::MOVE> solution;
    auto startTime = high_resolution_clock::now();

    if (!databaseFile.empty()) {
        IDAstarSolver<RubiksCubeBitboard, HashBitboard> solver(cube, databaseFile);
        solution = solver.solve();
        cube = solver.rubiksCube;
        cout << "Solver: IDA* with corner database\n";
    } else {
        IDDFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, 8);
        solution = solver.solve();
        cube = solver.rubiksCube;
        cout << "Solver: IDDFS\n";
    }

    auto stopTime = high_resolution_clock::now();
    auto solveTime = duration_cast<microseconds>(stopTime - startTime);

    cout << "Solution: ";
    printMoves(solution);
    cout << "\nTime taken: " << solveTime.count() << " microseconds";
    cout << "\nSolved: " << (cube.isSolved() ? "yes" : "no") << "\n";

    waitBeforeClosing(launchedWithoutArguments);
    return cube.isSolved() ? 0 : 2;
}
