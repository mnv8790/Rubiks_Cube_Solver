#ifndef IDASTARSOLVER_H
#define IDASTARSOLVER_H

#include "../Model/RubiksCube.h"
#include "../PatternDatabase/CornerPatternDatabase.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

template<typename T, typename H>
class IDAstarSolver {
private:
    CornerPatternDatabase cornerDB;
    bool hasDatabase = false;
    vector<RubiksCube::MOVE> answer;

    int heuristic(const T &cube) const {
        if (!hasDatabase) return 0;
        return cornerDB.getNumMoves(cube);
    }

    bool sameFace(RubiksCube::MOVE a, RubiksCube::MOVE b) const {
        return static_cast<int>(a) / 3 == static_cast<int>(b) / 3;
    }

    bool boundedSearch(T &cube, int depth, int bound, bool hasPrevious, RubiksCube::MOVE previous, int &nextBound) {
        int score = depth + heuristic(cube);
        if (score > bound) {
            nextBound = min(nextBound, score);
            return false;
        }

        if (cube.isSolved()) return true;

        for (int i = 0; i < 18; i++) {
            RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(i);
            if (hasPrevious && sameFace(move, previous)) continue;

            cube.move(move);
            answer.push_back(move);

            if (boundedSearch(cube, depth + 1, bound, true, move, nextBound)) return true;

            answer.pop_back();
            cube.invert(move);
        }
        return false;
    }

public:
    T rubiksCube;

    explicit IDAstarSolver(T cube) : rubiksCube(cube) {}

    IDAstarSolver(T cube, const string &fileName) : rubiksCube(cube) {
        hasDatabase = cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve() {
        int bound = heuristic(rubiksCube);
        if (bound == 0 && !rubiksCube.isSolved()) bound = 1;

        while (true) {
            answer.clear();
            T work = rubiksCube;
            int nextBound = 1000000;

            if (boundedSearch(work, 0, bound, false, RubiksCube::MOVE::U, nextBound)) {
                rubiksCube = work;
                assert(rubiksCube.isSolved());
                return answer;
            }

            if (nextBound == 1000000) return answer;
            bound = nextBound;
        }
    }
};

#endif
