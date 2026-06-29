CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
BIN_DIR  = bin

COMMON_SOURCES = \
	Model/RubiksCube.cpp \
	Model/RubicsCube1dArray.cpp \
	Model/RubiksCube3dArray.cpp \
	Model/RubiksCubeBitboard.cpp \
	PatternDatabase/math.cpp \
	PatternDatabase/NibbleArray.cpp \
	PatternDatabase/PatternDatabase.cpp \
	PatternDatabase/CornerPatternDatabase.cpp \
	PatternDatabase/CornerDBMaker.cpp

.PHONY: all main test run run_test clean

all: main test

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

main: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) main.cpp $(COMMON_SOURCES) -o $(BIN_DIR)/rubiks_solver

test: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) tests.cpp Model/RubiksCube.cpp PatternDatabase/math.cpp PatternDatabase/NibbleArray.cpp PatternDatabase/PatternDatabase.cpp PatternDatabase/CornerPatternDatabase.cpp PatternDatabase/CornerDBMaker.cpp -o $(BIN_DIR)/rubiks_tests

run: main
	./$(BIN_DIR)/rubiks_solver R2 U B

run_test: test
	./$(BIN_DIR)/rubiks_tests

clean:
	rm -rf $(BIN_DIR)
