# Rubik's Cube Solver in C++

This is a C++20 self-project for solving a 3x3 Rubik's Cube using state-space search. The project includes multiple cube representations, basic search solvers, and an IDA* solver inspired by Korf's approach with a corner pattern database heuristic.

The goal was not to build a fully optimized production-level cube solver. I built this mainly to understand how cube states can be represented in code and how search algorithms behave when the state space becomes very large.

## Why I built this

I wanted a project that connects data structures, object-oriented programming, and algorithms in one place. A Rubik's Cube is useful for this because every move creates a new state, and the solver has to search through possible move sequences to reach the solved cube.

## What the project does

- Represents a 3x3 Rubik's Cube using 1D array, 3D array, and bitboard models.
- Supports all 18 standard moves: `L L' L2 R R' R2 U U' U2 D D' D2 F F' F2 B B' B2`.
- Implements BFS, DFS, and IDDFS for basic state-space search.
- Implements IDA* as the more advanced search approach.
- Supports a corner pattern database heuristic for IDA*.
- Prints the scramble, cube state, solution moves, solve time, and solved status.

## Cube representation

The project keeps three cube models so different storage styles can be compared:

- **1D array model** stores all 54 stickers in a single linear array.
- **3D array model** stores stickers face-by-face in a more visual format.
- **Bitboard model** stores compact face data using integer-based encoding.

All models follow the same base `RubiksCube` interface. This uses OOP concepts like inheritance, virtual functions, overriding, and operator overloading, while keeping the solver code separate from the cube representation.

## Solvers implemented

- **BFS** explores states level by level and is mainly useful for small depths.
- **DFS** explores one path deeply before backtracking.
- **IDDFS** runs DFS with increasing depth limits, which makes it useful for short scrambles.
- **IDA*** uses a depth limit with a heuristic estimate to reduce unnecessary search.

## Project highlight: IDA*

IDA* can be understood as depth-first search with a smarter cutoff. It checks whether the current path length plus an estimated remaining cost is too high. If it is too high, that path is skipped for the current search limit.

This project is **inspired by Korf's approach**, where IDA* is combined with pattern databases. In this project, a corner pattern database can be loaded and used as a heuristic for IDA*. It should not be treated as a complete reimplementation of the original full Korf solver.

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

## How to build

Direct build with `g++`:

```bash
g++ -std=c++20 main.cpp Model/RubiksCube.cpp Model/RubicsCube1dArray.cpp Model/RubiksCube3dArray.cpp Model/RubiksCubeBitboard.cpp PatternDatabase/math.cpp PatternDatabase/NibbleArray.cpp PatternDatabase/PatternDatabase.cpp PatternDatabase/CornerPatternDatabase.cpp PatternDatabase/CornerDBMaker.cpp -o rubiks_solver.exe
```

The solver classes are template-based headers, so the `Solver/*.h` files do not need to be passed separately to `g++`.

Using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## How to run

Default run:

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

Run IDA* with the provided reference database file:

```bash
./rubiks_solver.exe --db ..\Check_these\Database.txt R U
```

Default runs are meant for shorter scrambles so the project remains easy to test and explain.

## Sample output

```text
Scramble: R2 U B
Solver: IDDFS
Solution: B' U' R2
Time taken: 13407 microseconds
Solved: yes
```

## What I learned

- How a Rubik's Cube can be represented as a program state.
- How BFS, DFS, IDDFS, and IDA* behave differently on the same problem.
- Why heuristics matter when the search space becomes large.
- How pattern databases can store precomputed information to guide search.
- How OOP can help separate cube models from solving algorithms.

## Limitations

- The default solver is intended for short scrambles, not arbitrary full-depth cube solving.
- BFS and DFS become impractical quickly as scramble depth increases.
- The IDA* implementation uses a corner pattern database heuristic, not a complete set of full-cube pattern databases.
- The project is mainly for learning and interview explanation, not a production cube-solving engine.

## Future improvements

- Add stronger pruning rules to reduce repeated or unnecessary move sequences.
- Add more pattern databases for better IDA* estimates.
- Improve benchmarking across all cube representations.
- Add unit tests for move correctness and solver behavior.
- Add a cleaner command-line interface for choosing solver type and scramble length.

## References

- Richard E. Korf's work on solving Rubik's Cube using IDA* and pattern databases.
- Rubik's Cube state-space search concepts.
- Pattern database heuristics for search problems.
