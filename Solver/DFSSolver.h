#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include "../Model/RubiksCube.h"

#include <vector>

template<typename T, typename H>
class DFSSolver {
private:
    int maxDepth;
    vector<RubiksCube::MOVE> path;

    bool sameFace(RubiksCube::MOVE a, RubiksCube::MOVE b) {
        return static_cast<int>(a) / 3 == static_cast<int>(b) / 3;
    }

    bool search(int depth, bool hasPrevious, RubiksCube::MOVE previous) {
        if (rubiksCube.isSolved()) return true;
        if (depth == maxDepth) return false;

        for (int i = 0; i < 18; i++) {
            RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(i);
            if (hasPrevious && sameFace(move, previous)) continue;

            rubiksCube.move(move);
            path.push_back(move);

            if (search(depth + 1, true, move)) return true;

            path.pop_back();
            rubiksCube.invert(move);
        }
        return false;
    }

public:
    T rubiksCube;

    DFSSolver(T cube, int depthLimit = 8) : maxDepth(depthLimit), rubiksCube(cube) {}

    vector<RubiksCube::MOVE> solve() {
        path.clear();
        search(0, false, RubiksCube::MOVE::U);
        return path;
    }
};

#endif
