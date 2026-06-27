# Rubik's Cube Solver

This is a C++20 Rubik's Cube solver project focused on state-space search algorithms. The main highlight of the project is the implementation of **IDA* (Iterative Deepening A*)**, inspired by **Korf's Algorithm**, with support for a corner pattern database heuristic.

C++ is used because Rubik's Cube solving involves a very large search space, so performance and memory control are important.

A 3x3 Rubik's Cube has about `4.3 × 10^19` possible states. It is also known that any valid cube state can be solved in 20 moves or fewer, commonly called **God's Number**. This makes the Rubik's Cube an interesting problem for studying search algorithms, heuristics, and optimization.

## What the project does

* Represents a 3x3 Rubik's Cube using three model styles: 1D array, 3D array, and bitboard.
* Supports all 18 standard moves: `L L' L2 R R' R2 U U' U2 D D' D2 F F' F2 B B' B2`.
* Implements basic solvers such as BFS, DFS, and IDDFS for comparison.
* Implements **IDA*** as the main advanced solver.
* Supports **corner pattern database heuristics** for improving IDA* search.
* Prints the scramble, cube state, solution moves, solve time, and solved status.

## Project highlight: IDA* and Korf's Algorithm

The most important part of this project is the **IDA*** solver.

IDA* combines the low memory usage of depth-first search with heuristic-based pruning. Instead of blindly exploring every possible move sequence, it uses a cost estimate to avoid paths that are unlikely to lead to a short solution.

This approach is inspired by **Korf's Algorithm**, which uses IDA* together with pattern databases to solve Rubik's Cube states efficiently. In this project, a corner pattern database can be loaded and used as a heuristic for the IDA* solver.

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

Direct build with `g++`:

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

Run IDA* with a corner database file:

```bash
./rubiks_solver.exe --db ..\Check_these\Database.txt R U
```

## Sample output

```text
Solver: IDA*
Solution: U' R'
Time taken: 8421 microseconds
Solved: yes
```

## Notes

The default solver is meant for short scrambles so the program stays easy to run and explain. For deeper scrambles, **IDA*** with a prepared corner pattern database is the better approach.

This project is mainly built to understand cube representation, graph/state-space search, heuristic search, and performance differences between solver strategies.

## References

* Korf's Rubik's Cube solving approach using IDA* and pattern databases
* God's Number for Rubik's Cube: 20 moves
* Rubik's Cube state-space search and heuristic algorithms
