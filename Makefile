CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc
SRC := src/main.cpp src/Parser.cpp src/Environment.cpp src/Interpreter.cpp

.PHONY: all test clean

all: interpreter

interpreter: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o interpreter

test: interpreter
	cd tests && python3 test_interpreter.py

clean:
	rm -f interpreter
