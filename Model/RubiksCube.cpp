#include "RubiksCube.h"

#include <cstdlib>
#include <ctime>

char RubiksCube::getColorLetter(COLOR color) {
    switch (color) {
        case COLOR::WHITE: return 'W';
        case COLOR::GREEN: return 'G';
        case COLOR::RED: return 'R';
        case COLOR::BLUE: return 'B';
        case COLOR::ORANGE: return 'O';
        case COLOR::YELLOW: return 'Y';
    }
    return '?';
}

RubiksCube::COLOR RubiksCube::getColorFromLetter(char color) {
    switch (color) {
        case 'G': return COLOR::GREEN;
        case 'R': return COLOR::RED;
        case 'B': return COLOR::BLUE;
        case 'O': return COLOR::ORANGE;
        case 'Y': return COLOR::YELLOW;
        default: return COLOR::WHITE;
    }
}

string RubiksCube::getMove(MOVE move) {
    switch (move) {
        case MOVE::L: return "L";
        case MOVE::LPRIME: return "L'";
        case MOVE::L2: return "L2";
        case MOVE::R: return "R";
        case MOVE::RPRIME: return "R'";
        case MOVE::R2: return "R2";
        case MOVE::U: return "U";
        case MOVE::UPRIME: return "U'";
        case MOVE::U2: return "U2";
        case MOVE::D: return "D";
        case MOVE::DPRIME: return "D'";
        case MOVE::D2: return "D2";
        case MOVE::F: return "F";
        case MOVE::FPRIME: return "F'";
        case MOVE::F2: return "F2";
        case MOVE::B: return "B";
        case MOVE::BPRIME: return "B'";
        case MOVE::B2: return "B2";
    }
    return "?";
}

void RubiksCube::print() const {
    cout << "\n";
    for (int row = 0; row < 3; row++) {
        cout << "      ";
        for (int col = 0; col < 3; col++) cout << getColorLetter(getColor(FACE::UP, row, col)) << ' ';
        cout << "\n";
    }

    cout << "\n";
    for (int row = 0; row < 3; row++) {
        for (FACE face: {FACE::LEFT, FACE::FRONT, FACE::RIGHT, FACE::BACK}) {
            for (int col = 0; col < 3; col++) cout << getColorLetter(getColor(face, row, col)) << ' ';
            cout << " ";
        }
        cout << "\n";
    }

    cout << "\n";
    for (int row = 0; row < 3; row++) {
        cout << "      ";
        for (int col = 0; col < 3; col++) cout << getColorLetter(getColor(FACE::DOWN, row, col)) << ' ';
        cout << "\n";
    }
    cout << "\n";
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffleCube(unsigned int times) {
    vector<MOVE> moves;
    srand(static_cast<unsigned>(time(nullptr)));
    for (unsigned int i = 0; i < times; i++) {
        MOVE selected = static_cast<MOVE>(rand() % 18);
        moves.push_back(selected);
        move(selected);
    }
    return moves;
}

RubiksCube &RubiksCube::move(MOVE move) {
    switch (move) {
        case MOVE::L: return l();
        case MOVE::LPRIME: return lPrime();
        case MOVE::L2: return l2();
        case MOVE::R: return r();
        case MOVE::RPRIME: return rPrime();
        case MOVE::R2: return r2();
        case MOVE::U: return u();
        case MOVE::UPRIME: return uPrime();
        case MOVE::U2: return u2();
        case MOVE::D: return d();
        case MOVE::DPRIME: return dPrime();
        case MOVE::D2: return d2();
        case MOVE::F: return f();
        case MOVE::FPRIME: return fPrime();
        case MOVE::F2: return f2();
        case MOVE::B: return b();
        case MOVE::BPRIME: return bPrime();
        case MOVE::B2: return b2();
    }
    return *this;
}

RubiksCube &RubiksCube::invert(MOVE move) {
    switch (move) {
        case MOVE::L: return lPrime();
        case MOVE::LPRIME: return l();
        case MOVE::R: return rPrime();
        case MOVE::RPRIME: return r();
        case MOVE::U: return uPrime();
        case MOVE::UPRIME: return u();
        case MOVE::D: return dPrime();
        case MOVE::DPRIME: return d();
        case MOVE::F: return fPrime();
        case MOVE::FPRIME: return f();
        case MOVE::B: return bPrime();
        case MOVE::BPRIME: return b();
        default: return this->move(move);
    }
}

array<char, 54> RubiksCube::solvedStickerArray() {
    array<char, 54> stickers{};
    for (int face = 0; face < 6; face++) {
        char color = getColorLetter(static_cast<COLOR>(face));
        for (int cell = 0; cell < 9; cell++) stickers[face * 9 + cell] = color;
    }
    return stickers;
}

bool RubiksCube::isStickerArraySolved(const array<char, 54> &stickers) {
    for (int face = 0; face < 6; face++) {
        char expected = stickers[face * 9 + 4];
        for (int cell = 0; cell < 9; cell++) {
            if (stickers[face * 9 + cell] != expected) return false;
        }
    }
    return true;
}

int RubiksCube::flatIndex(FACE face, int row, int col) {
    return static_cast<int>(face) * 9 + row * 3 + col;
}

RubiksCube::StickerPlace RubiksCube::placeFromFlatIndex(int index) {
    int face = index / 9;
    int row = (index % 9) / 3;
    int col = index % 3;

    switch (static_cast<FACE>(face)) {
        case FACE::UP: return {col - 1, 1, row - 1, 0, 1, 0};
        case FACE::DOWN: return {col - 1, -1, 1 - row, 0, -1, 0};
        case FACE::FRONT: return {col - 1, 1 - row, 1, 0, 0, 1};
        case FACE::BACK: return {1 - col, 1 - row, -1, 0, 0, -1};
        case FACE::LEFT: return {-1, 1 - row, col - 1, -1, 0, 0};
        case FACE::RIGHT: return {1, 1 - row, 1 - col, 1, 0, 0};
    }
    return {0, 0, 0, 0, 0, 0};
}

int RubiksCube::flatIndexFromPlace(const StickerPlace &place) {
    if (place.ny == 1) return flatIndex(FACE::UP, place.z + 1, place.x + 1);
    if (place.ny == -1) return flatIndex(FACE::DOWN, 1 - place.z, place.x + 1);
    if (place.nz == 1) return flatIndex(FACE::FRONT, 1 - place.y, place.x + 1);
    if (place.nz == -1) return flatIndex(FACE::BACK, 1 - place.y, 1 - place.x);
    if (place.nx == -1) return flatIndex(FACE::LEFT, 1 - place.y, place.z + 1);
    return flatIndex(FACE::RIGHT, 1 - place.y, 1 - place.z);
}

static void rotatePoint(int &x, int &y, int &z, char axis, int turns) {
    turns = ((turns % 4) + 4) % 4;
    while (turns-- > 0) {
        int ox = x, oy = y, oz = z;
        if (axis == 'x') { x = ox; y = -oz; z = oy; }
        if (axis == 'y') { x = oz; y = oy; z = -ox; }
        if (axis == 'z') { x = -oy; y = ox; z = oz; }
    }
}

static void rotateLayer(array<char, 54> &stickers, char axis, int layer, int turns) {
    array<char, 54> next = stickers;
    for (int i = 0; i < 54; i++) {
        RubiksCube::StickerPlace place = RubiksCube::placeFromFlatIndex(i);
        int layerValue = axis == 'x' ? place.x : axis == 'y' ? place.y : place.z;
        if (layerValue != layer) continue;

        rotatePoint(place.x, place.y, place.z, axis, turns);
        rotatePoint(place.nx, place.ny, place.nz, axis, turns);
        next[RubiksCube::flatIndexFromPlace(place)] = stickers[i];
    }
    stickers = next;
}

void RubiksCube::applyMoveToStickerArray(array<char, 54> &stickers, MOVE move) {
    switch (move) {
        case MOVE::U: rotateLayer(stickers, 'y', 1, 1); break;
        case MOVE::UPRIME: rotateLayer(stickers, 'y', 1, -1); break;
        case MOVE::U2: rotateLayer(stickers, 'y', 1, 2); break;
        case MOVE::D: rotateLayer(stickers, 'y', -1, -1); break;
        case MOVE::DPRIME: rotateLayer(stickers, 'y', -1, 1); break;
        case MOVE::D2: rotateLayer(stickers, 'y', -1, 2); break;
        case MOVE::L: rotateLayer(stickers, 'x', -1, -1); break;
        case MOVE::LPRIME: rotateLayer(stickers, 'x', -1, 1); break;
        case MOVE::L2: rotateLayer(stickers, 'x', -1, 2); break;
        case MOVE::R: rotateLayer(stickers, 'x', 1, 1); break;
        case MOVE::RPRIME: rotateLayer(stickers, 'x', 1, -1); break;
        case MOVE::R2: rotateLayer(stickers, 'x', 1, 2); break;
        case MOVE::F: rotateLayer(stickers, 'z', 1, 1); break;
        case MOVE::FPRIME: rotateLayer(stickers, 'z', 1, -1); break;
        case MOVE::F2: rotateLayer(stickers, 'z', 1, 2); break;
        case MOVE::B: rotateLayer(stickers, 'z', -1, -1); break;
        case MOVE::BPRIME: rotateLayer(stickers, 'z', -1, 1); break;
        case MOVE::B2: rotateLayer(stickers, 'z', -1, 2); break;
    }
}

string RubiksCube::getCornerColorString(uint8_t index) const {
    static const array<array<pair<FACE, pair<int, int>>, 3>, 8> corners = {{
        {{{FACE::UP, {2, 2}}, {FACE::FRONT, {0, 2}}, {FACE::RIGHT, {0, 0}}}},
        {{{FACE::UP, {2, 0}}, {FACE::FRONT, {0, 0}}, {FACE::LEFT, {0, 2}}}},
        {{{FACE::UP, {0, 0}}, {FACE::BACK, {0, 2}}, {FACE::LEFT, {0, 0}}}},
        {{{FACE::UP, {0, 2}}, {FACE::BACK, {0, 0}}, {FACE::RIGHT, {0, 2}}}},
        {{{FACE::DOWN, {0, 2}}, {FACE::FRONT, {2, 2}}, {FACE::RIGHT, {2, 0}}}},
        {{{FACE::DOWN, {0, 0}}, {FACE::FRONT, {2, 0}}, {FACE::LEFT, {2, 2}}}},
        {{{FACE::DOWN, {2, 2}}, {FACE::BACK, {2, 0}}, {FACE::RIGHT, {2, 2}}}},
        {{{FACE::DOWN, {2, 0}}, {FACE::BACK, {2, 2}}, {FACE::LEFT, {2, 0}}}}
    }};

    string result;
    for (const auto &part: corners[index]) {
        result += getColorLetter(getColor(part.first, part.second.first, part.second.second));
    }
    return result;
}

uint8_t RubiksCube::getCornerIndex(uint8_t index) const {
    string corner = getCornerColorString(index);
    uint8_t value = 0;
    for (char color: corner) {
        if (color == 'Y') value |= 4;
        if (color == 'O') value |= 2;
        if (color == 'G') value |= 1;
    }
    return value;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t index) const {
    string corner = getCornerColorString(index);
    char topBottom = 'W';
    for (char color: corner) {
        if (color == 'W' || color == 'Y') {
            topBottom = color;
            break;
        }
    }
    if (corner[1] == topBottom) return 1;
    if (corner[2] == topBottom) return 2;
    return 0;
}
