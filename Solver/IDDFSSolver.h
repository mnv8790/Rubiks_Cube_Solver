#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H

#include "DFSSolver.h"
#include "../Model/RubiksCube.h"

#include <vector>

template<typename T, typename H>
class IDDFSSolver {
private:
    int maxDepth;
    vector<RubiksCube::MOVE> answer;

public:
    T rubiksCube;

    IDDFSSolver(T cube, int depthLimit = 7) : maxDepth(depthLimit), rubiksCube(cube) {}

    vector<RubiksCube::MOVE> solve() {
        answer.clear();
        for (int depth = 0; depth <= maxDepth; depth++) {
            DFSSolver<T, H> dfs(rubiksCube, depth);
            answer = dfs.solve();
            if (dfs.rubiksCube.isSolved()) {
                rubiksCube = dfs.rubiksCube;
                return answer;
            }
        }
        return answer;
    }
};

#endif
