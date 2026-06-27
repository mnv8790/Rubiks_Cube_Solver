# Rubik's Cube Solver

A C++ Rubik's Cube solver project using the same layered structure as the reference projects.
The program also prints the time taken to solve each scramble.

## Folder structure

- `Model/` - cube model base class plus 1D array, 3D array, and bitboard versions.
- `Solver/` - BFS, DFS, IDDFS, and IDA* solver headers.
- `PatternDatabase/` - nibble storage, permutation ranking, corner pattern database, and DB maker.

## What is different from the references

This project keeps the same level and layout, but the move logic is rewritten. Instead of copying long face-swap blocks, all models use a shared sticker-coordinate rotation helper from `RubiksCube.cpp`. The three model files still store the cube differently.

## Build

Direct build with g++:

```bash
g++ -std=c++20 main.cpp Model/RubiksCube.cpp PatternDatabase/math.cpp PatternDatabase/NibbleArray.cpp PatternDatabase/PatternDatabase.cpp PatternDatabase/CornerPatternDatabase.cpp PatternDatabase/CornerDBMaker.cpp -o rubiks_solver.exe
```

Using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Run

Default scramble:

```bash
./rubiks_solver.exe
```

On Windows, double-click `Run_Rubiks_Solver.bat` if the console closes too quickly.

Custom scramble:

```bash
./rubiks_solver.exe R U F'
```

IDA* with a corner database file:

```bash
./rubiks_solver.exe --db Check_these/Database.txt R U F'
```

For normal checking, keep scrambles short. Full cube solving can become slow without a prepared pattern database.
