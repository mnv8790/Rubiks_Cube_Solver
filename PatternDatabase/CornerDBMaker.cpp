#include "CornerDBMaker.h"

#include <queue>

CornerDBMaker::CornerDBMaker(string fileName) : fileName(fileName), cornerDB() {}

CornerDBMaker::CornerDBMaker(string fileName, uint8_t initialValue)
        : fileName(fileName), cornerDB(initialValue) {}

bool CornerDBMaker::bfsAndStore() {
    queue<RubiksCubeBitboard> pending;
    RubiksCubeBitboard start;

    pending.push(start);
    cornerDB.setNumMoves(start, 0);

    int depth = 0;
    while (!pending.empty() && depth < 8) {
        int levelSize = static_cast<int>(pending.size());
        depth++;

        for (int count = 0; count < levelSize; count++) {
            RubiksCubeBitboard current = pending.front();
            pending.pop();

            for (int i = 0; i < 18; i++) {
                RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(i);
                RubiksCubeBitboard next = current;
                next.move(move);

                if (cornerDB.setNumMoves(next, static_cast<uint8_t>(depth))) {
                    pending.push(next);
                }
            }
        }
    }

    cornerDB.toFile(fileName);
    return true;
}
