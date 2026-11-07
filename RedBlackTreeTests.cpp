
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "RedBlackTree.h"

using namespace std;

// Tests the empty constructor.
void TestSimpleConstructor() {
    cout << "Testing Simple Constructor..." << endl;

    RedBlackTree rbt;

    assert(rbt.Size() == 0);
    assert(rbt.ToInfixString() == "");
    assert(!rbt.Contains(10));

    cout << "PASSED!" << endl << endl;
}

// Tests the constructor that creates a tree with one value.
void TestConstructor() {
    cout << "Testing Constructor..." << endl;

    RedBlackTree rbt(15);

    assert(rbt.Size() == 1);
    assert(rbt.Contains(15));
    assert(rbt.ToInfixString() == " B15 ");

    cout << "PASSED!" << endl << endl;
}

// Tests inserting the first node.
void TestInsertFirstNode() {
    cout << "Testing First Insert..." << endl;

    RedBlackTree rbt;
    rbt.Insert(30);

    assert(rbt.Size() == 1);
    assert(rbt.Contains(30));
    assert(rbt.ToInfixString() == " B30 ");

    cout << "PASSED!" << endl << endl;
}

// Tests inserting a second node.
void TestInsertSecondNode() {
    cout << "Testing Second Insert..." << endl;

    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);

    assert(rbt1.Size() == 2);
    assert(rbt1.Contains(15));
    assert(rbt1.Contains(30));

    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(45);

    assert(rbt2.Size() == 2);
    assert(rbt2.Contains(30));
    assert(rbt2.Contains(45));

    cout << "PASSED!" << endl << endl;
}

// Tests the left-left, left-right, and no-rotation cases.
void TestInsertThirdNode() {
    cout << "Testing Third Insert..." << endl;

    // Left-left case.
    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);
    rbt1.Insert(10);

    assert(rbt1.Size() == 3);
    assert(rbt1.ToPrefixString() == " B15  R10  R30 ");

    // Left-right case.
    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(15);
    rbt2.Insert(25);

    assert(rbt2.Size() == 3);
    assert(rbt2.ToPrefixString() == " B25  R15  R30 ");

    // No rotation needed.
    RedBlackTree rbt3;
    rbt3.Insert(30);
    rbt3.Insert(15);
    rbt3.Insert(45);

    assert(rbt3.Size() == 3);
    assert(rbt3.ToPrefixString() == " B30  R15  R45 ");

    cout << "PASSED!" << endl << endl;
}

// Tests inserting a fourth node and recoloring.
void TestInsertFourthNode() {
    cout << "Testing Fourth Insert..." << endl;

    // Red parent and red uncle: recoloring.
    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);
    rbt1.Insert(45);
    rbt1.Insert(10);

    assert(rbt1.Size() == 4);
    assert(rbt1.Contains(10));
    assert(rbt1.Contains(15));
    assert(rbt1.Contains(30));
    assert(rbt1.Contains(45));

    // Symmetric recoloring case.
    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(45);
    rbt2.Insert(15);
    rbt2.Insert(50);

    assert(rbt2.Size() == 4);
    assert(rbt2.Contains(15));
    assert(rbt2.Contains(30));
    assert(rbt2.Contains(45));
    assert(rbt2.Contains(50));

    cout << "PASSED!" << endl << endl;
}

// Tests inserting a fifth node.
void TestInsertFifthNode() {
    cout << "Testing Fifth Insert..." << endl;

    RedBlackTree rbt;
    rbt.Insert(30);
    rbt.Insert(15);
    rbt.Insert(45);
    rbt.Insert(10);
    rbt.Insert(25);

    assert(rbt.Size() == 5);
    assert(rbt.Contains(10));
    assert(rbt.Contains(15));
    assert(rbt.Contains(25));
    assert(rbt.Contains(30));
    assert(rbt.Contains(45));

    cout << "PASSED!" << endl << endl;
}

// Tests right-right and right-left rotations.
void TestRightSideRotations() {
    cout << "Testing Right-Side Rotations..." << endl;

    // Right-right case.
    RedBlackTree rbt1;
    rbt1.Insert(10);
    rbt1.Insert(20);
    rbt1.Insert(30);

    assert(rbt1.Size() == 3);
    assert(rbt1.ToPrefixString() == " B20  R10  R30 ");

    // Right-left case.
    RedBlackTree rbt2;
    rbt2.Insert(10);
    rbt2.Insert(30);
    rbt2.Insert(20);

    assert(rbt2.Size() == 3);
    assert(rbt2.ToPrefixString() == " B20  R10  R30 ");

    cout << "PASSED!" << endl << endl;
}

// Tests all three traversal methods.
void TestToStrings() {
    cout << "Testing Traversal Strings..." << endl;

    RedBlackTree rbt;
    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);

    assert(rbt.ToInfixString() == " R10  B20  R30 ");
    assert(rbt.ToPrefixString() == " B20  R10  R30 ");
    assert(rbt.ToPostfixString() == " R10  R30  B20 ");

    cout << "PASSED!" << endl << endl;
}

// Tests additional insertion sequences.
void TestAdditionalInsertionSequences() {
    cout << "Testing Additional Insertion Sequences..." << endl;

    RedBlackTree rbt1;
    rbt1.Insert(15);
    rbt1.Insert(13);
    rbt1.Insert(20);
    rbt1.Insert(12);

    assert(rbt1.Size() == 4);
    assert(rbt1.Contains(12));
    assert(rbt1.Contains(13));
    assert(rbt1.Contains(15));
    assert(rbt1.Contains(20));

    RedBlackTree rbt2;
    rbt2.Insert(12);
    rbt2.Insert(11);
    rbt2.Insert(15);
    rbt2.Insert(5);
    rbt2.Insert(13);
    rbt2.Insert(7);

    assert(rbt2.Size() == 6);
    assert(rbt2.Contains(5));
    assert(rbt2.Contains(7));
    assert(rbt2.Contains(11));
    assert(rbt2.Contains(12));
    assert(rbt2.Contains(13));
    assert(rbt2.Contains(15));

    RedBlackTree rbt3;
    rbt3.Insert(12);
    rbt3.Insert(10);
    rbt3.Insert(8);

    assert(rbt3.Size() == 3);
    assert(rbt3.Contains(8));
    assert(rbt3.Contains(10));
    assert(rbt3.Contains(12));

    cout << "PASSED!" << endl << endl;
}

// Tests inserting a larger number of nodes in ascending order.
void TestLargeTree() {
    cout << "Testing Large Tree..." << endl;

    RedBlackTree rbt;

    for (int i = 1; i <= 100; i++) {
        rbt.Insert(i);
    }

    assert(rbt.Size() == 100);
    assert(rbt.GetMin() == 1);
    assert(rbt.GetMax() == 100);

    for (int i = 1; i <= 100; i++) {
        assert(rbt.Contains(i));
    }

    assert(!rbt.Contains(0));
    assert(!rbt.Contains(101));

    cout << "PASSED!" << endl << endl;
}

// Tests the copy constructor and verifies that the copy is independent.
void TestCopyConstructor() {
    cout << "Testing Copy Constructor..." << endl;

    RedBlackTree original;
    original.Insert(20);
    original.Insert(10);
    original.Insert(30);
    original.Insert(5);
    original.Insert(15);
    original.Insert(25);

    RedBlackTree copy(original);

    assert(copy.Size() == original.Size());
    assert(copy.ToInfixString() == original.ToInfixString());
    assert(copy.ToPrefixString() == original.ToPrefixString());
    assert(copy.ToPostfixString() == original.ToPostfixString());

    // Changing the original should not change the copy.
    original.Insert(40);

    assert(original.Size() == 7);
    assert(copy.Size() == 6);
    assert(!copy.Contains(40));

    // Also test copying an empty tree.
    RedBlackTree empty;
    RedBlackTree emptyCopy(empty);

    assert(emptyCopy.Size() == 0);
    assert(emptyCopy.ToInfixString() == "");

    cout << "PASSED!" << endl << endl;
}

// Tests Contains().
void TestContains() {
    cout << "Testing Contains..." << endl;

    RedBlackTree rbt;
    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);
    rbt.Insert(5);
    rbt.Insert(15);

    assert(rbt.Contains(20));
    assert(rbt.Contains(10));
    assert(rbt.Contains(30));
    assert(rbt.Contains(5));
    assert(rbt.Contains(15));

    assert(!rbt.Contains(0));
    assert(!rbt.Contains(12));
    assert(!rbt.Contains(40));

    cout << "PASSED!" << endl << endl;
}

// Tests GetMin() and GetMax().
void TestGetMinimumMaximum() {
    cout << "Testing GetMin and GetMax..." << endl;

    // Empty tree should throw an exception.
    RedBlackTree empty;

    bool minThrew = false;
    bool maxThrew = false;

    try {
        empty.GetMin();
    }
    catch (const invalid_argument&) {
        minThrew = true;
    }

    try {
        empty.GetMax();
    }
    catch (const invalid_argument&) {
        maxThrew = true;
    }

    assert(minThrew);
    assert(maxThrew);

    // Single-node tree.
    RedBlackTree single;
    single.Insert(42);

    assert(single.GetMin() == 42);
    assert(single.GetMax() == 42);

    // Multiple-node tree.
    RedBlackTree rbt;
    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);
    rbt.Insert(5);
    rbt.Insert(15);

    assert(rbt.GetMin() == 5);
    assert(rbt.GetMax() == 30);

    cout << "PASSED!" << endl << endl;
}

// Tests that inserting a duplicate throws an exception.
void TestDuplicateInsertion() {
    cout << "Testing Duplicate Insertion..." << endl;

    RedBlackTree rbt;
    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);

    bool threw = false;

    try {
        rbt.Insert(20);
    }
    catch (const invalid_argument&) {
        threw = true;
    }

    assert(threw);
    assert(rbt.Size() == 3);
    assert(rbt.Contains(20));

    cout << "PASSED!" << endl << endl;
}

// Runs the private tests defined in RedBlackTree.cpp.
void TestPrivateTests() {
    cout << "Testing PrivateTests..." << endl;

    RedBlackTree rbt;
    rbt.PrivateTests();

    cout << "PASSED!" << endl << endl;
}

int main() {
    TestSimpleConstructor();
    TestConstructor();
    TestInsertFirstNode();
    TestInsertSecondNode();
    TestInsertThirdNode();
    TestInsertFourthNode();
    TestInsertFifthNode();
    TestRightSideRotations();
    TestToStrings();
    TestAdditionalInsertionSequences();
    TestLargeTree();
    TestCopyConstructor();
    TestContains();
    TestGetMinimumMaximum();
    TestDuplicateInsertion();
    TestPrivateTests();

    cout << "ALL TESTS PASSED!!" << endl;

    return 0;
}
