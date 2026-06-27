#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "../Model/RubiksCube.h"

#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <vector>

template<typename T, typename H>
class BFSSolver {
private:
    unordered_map<T, bool, H> visited;
    unordered_map<T, RubiksCube::MOVE, H> reachedBy;
    vector<RubiksCube::MOVE> answer;

    T runBfs() {
        queue<T> pending;
        pending.push(rubiksCube);
        visited[rubiksCube] = true;

        while (!pending.empty()) {
            T current = pending.front();
            pending.pop();

            if (current.isSolved()) return current;

            for (int i = 0; i < 18; i++) {
                RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(i);
                T next = current;
                next.move(move);

                if (!visited[next]) {
                    visited[next] = true;
                    reachedBy[next] = move;
                    pending.push(next);
                }
            }
        }
        return rubiksCube;
    }

public:
    T rubiksCube;

    explicit BFSSolver(T cube) : rubiksCube(cube) {}

    vector<RubiksCube::MOVE> solve() {
        answer.clear();
        T solved = runBfs();
        assert(solved.isSolved());

        T cursor = solved;
        while (!(cursor == rubiksCube)) {
            RubiksCube::MOVE move = reachedBy[cursor];
            answer.push_back(move);
            cursor.invert(move);
        }

        reverse(answer.begin(), answer.end());
        rubiksCube = solved;
        return answer;
    }
};

#endif
