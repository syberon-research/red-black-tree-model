CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

all: rbt-tests

rbt-tests: RedBlackTree.cpp RedBlackTreeTests.cpp RedBlackTree.h
	$(CXX) $(CXXFLAGS) RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

test: rbt-tests
	./rbt-tests

clean:
	rm -f rbt-tests
