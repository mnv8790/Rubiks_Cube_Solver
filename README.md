# Rubik's Cube Solver

This is a C++20 Rubik's Cube solver built with the same project layering as the reference project: cube models, search solvers, and a corner pattern database. The code is kept at student-project level, but the move implementation is written differently so it is not just a copied version of the reference files.

## What the project does

- Represents a 3x3 Rubik's Cube using three model styles: 1D array, 3D array, and bitboard.
- Supports all 18 standard moves: `L L' L2 R R' R2 U U' U2 D D' D2 F F' F2 B B' B2`.
- Solves short scrambles using IDDFS by default.
- Supports IDA* when a corner pattern database file is provided.
- Prints the scramble, cube state, solution moves, solve time, and solved status.

## Folder structure

```text
Model/
  RubicsCube1dArray.cpp
  RubiksCube.cpp
  RubiksCube.h
  RubiksCube3dArray.cpp
  RubiksCubeBitboard.cpp

Solver/
  BFSSolver.h
  DFSSolver.h
  IDAstarSolver.h
  IDDFSSolver.h

PatternDatabase/
  CornerDBMaker.cpp
  CornerDBMaker.h
  CornerPatternDatabase.cpp
  CornerPatternDatabase.h
  NibbleArray.cpp
  NibbleArray.h
  PatternDatabase.cpp
  PatternDatabase.h
  PermutationIndexer.h
  math.cpp
  math.h
```

## How to build it

Direct build with g++:

```bash
g++ -std=c++20 main.cpp Model/RubiksCube.cpp PatternDatabase/math.cpp PatternDatabase/NibbleArray.cpp PatternDatabase/PatternDatabase.cpp PatternDatabase/CornerPatternDatabase.cpp PatternDatabase/CornerDBMaker.cpp -o rubiks_solver.exe
```

Using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## How to run it

Default scramble:

```bash
./rubiks_solver.exe
```

On Windows, double-click:

```text
Run_Rubiks_Solver.bat
```

Custom scramble:

```bash
./rubiks_solver.exe R U F'
./rubiks_solver.exe R2 U B
```

IDA* with the reference database file:

```bash
./rubiks_solver.exe --db ..\Check_these\Database.txt R U
```

## Sample output

```text
Solver: IDDFS
Solution: B' U' R2
Time taken: 14995 microseconds
Solved: yes
```

## Notes

The default solver is meant for short scrambles so the program stays easy to run and explain. Full random cube solving can be slow unless the pattern database is available and loaded with `--db`.
