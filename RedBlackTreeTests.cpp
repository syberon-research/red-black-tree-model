
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor() {
    cout << "Testing Simple Constructor..." << endl;

    RedBlackTree rbt;
    assert(rbt.ToInfixString() == "");
    assert(rbt.Size() == 0);

    cout << "PASSED!" << endl << endl;
}

void TestConstructor() {
    cout << "Testing Constructor With Int Input..." << endl;

    RedBlackTree rbt(15);
    assert(rbt.ToPrefixString() == " B15 ");
    assert(rbt.Size() == 1);

    cout << "PASSED!" << endl << endl;
}

void TestInsertFirstNode() {
    cout << "Testing Insert One Node..." << endl;

    RedBlackTree rbt;
    rbt.Insert(30);

    assert(rbt.ToPrefixString() == " B30 ");
    assert(rbt.Size() == 1);

    cout << "PASSED!" << endl << endl;
}

void TestInsertSecondNode() {
    cout << "Testing Insert Second Node..." << endl;

    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);
    assert(rbt1.ToPrefixString() == " B30  R15 ");

    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(45);
    assert(rbt2.ToPrefixString() == " B30  R45 ");

    cout << "PASSED!" << endl << endl;
}

void TestInsertThirdNode() {
    cout << "Testing Insert Third Node..." << endl;

    // Left-left case
    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);
    rbt1.Insert(10);
    assert(rbt1.ToPrefixString() == " B15  R10  R30 ");

    // Left-right case
    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(15);
    rbt2.Insert(25);
    assert(rbt2.ToPrefixString() == " B25  R15  R30 ");

    // No rotation needed
    RedBlackTree rbt3;
    rbt3.Insert(30);
    rbt3.Insert(15);
    rbt3.Insert(45);
    assert(rbt3.ToPrefixString() == " B30  R15  R45 ");

    cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode() {
    cout << "Testing Insert Fourth Node..." << endl;

    // Recoloring case: red parent and red uncle
    RedBlackTree rbt1;
    rbt1.Insert(30);
    rbt1.Insert(15);
    rbt1.Insert(45);
    rbt1.Insert(10);

    assert(rbt1.ToPrefixString() == " B30  B15  R10  B45 ");

    // Symmetric recoloring case
    RedBlackTree rbt2;
    rbt2.Insert(30);
    rbt2.Insert(45);
    rbt2.Insert(15);
    rbt2.Insert(50);

    assert(rbt2.ToPrefixString() == " B30  B15  B45  R50 ");

    cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode() {
    cout << "Testing Insert Fifth Node..." << endl;

    RedBlackTree rbt;
    rbt.Insert(30);
    rbt.Insert(15);
    rbt.Insert(45);
    rbt.Insert(10);
    rbt.Insert(25);

    assert(rbt.ToPrefixString() == " B30  B15  R10  R25  B45 ");
    assert(rbt.Size() == 5);

    cout << "PASSED!" << endl << endl;
}

void TestToStrings() {
    cout << "Testing ToString Methods..." << endl;

    RedBlackTree rbt;
    rbt.Insert(12);
    rbt.Insert(11);
    rbt.Insert(15);
    rbt.Insert(5);
    rbt.Insert(13);
    rbt.Insert(7);

    assert(rbt.ToPrefixString() ==
           " B12  B7  R5  R11  B15  R13 ");

    assert(rbt.ToInfixString() ==
           " R5  B7  R11  B12  R13  B15 ");

    assert(rbt.ToPostfixString() ==
           " R5  R11  B7  R13  B15  B12 ");

    cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests() {
    cout << "Testing Random Insert Stuff..." << endl;

    RedBlackTree rbt1;
    rbt1.Insert(15);
    rbt1.Insert(13);
    rbt1.Insert(20);
    rbt1.Insert(12);
    assert(rbt1.Size() == 4);

    RedBlackTree rbt2;
    rbt2.Insert(12);
    rbt2.Insert(11);
    rbt2.Insert(15);
    rbt2.Insert(5);
    rbt2.Insert(13);
    rbt2.Insert(7);
    assert(rbt2.Size() == 6);

    RedBlackTree rbt3;
    rbt3.Insert(12);
    rbt3.Insert(10);
    rbt3.Insert(8);
    assert(rbt3.Size() == 3);

    cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor() {
    cout << "Testing Copy Constructor..." << endl;

    RedBlackTree rbt1;
    rbt1.Insert(11);
    rbt1.Insert(23);
    rbt1.Insert(9);
    rbt1.Insert(52);
    rbt1.Insert(31);
    rbt1.Insert(4);

    assert(rbt1.ToPrefixString() ==
           " B11  B9  R4  B31  R23  R52 ");

    RedBlackTree rbt2(rbt1);

    assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());
    assert(rbt2.Size() == rbt1.Size());

    // Changing the original must not change the copy.
    rbt1.Insert(200);

    assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());
    assert(rbt2.Size() == 6);
    assert(rbt1.Size() == 7);

    cout << "PASSED!" << endl << endl;
}

void TestContains() {
    cout << "Testing Contains..." << endl;

    RedBlackTree rbt;
    assert(rbt.Contains(6) == false);

    rbt.Insert(40);
    rbt.Insert(22);
    rbt.Insert(15);
    rbt.Insert(31);
    rbt.Insert(55);
    rbt.Insert(12);
    rbt.Insert(17);
    rbt.Insert(29);
    rbt.Insert(34);

    assert(rbt.Contains(34));
    assert(rbt.Contains(40));
    assert(rbt.Contains(12));
    assert(rbt.Contains(55));

    assert(!rbt.Contains(6));
    assert(!rbt.Contains(100));
    assert(!rbt.Contains(33));

    cout << "PASSED!" << endl << endl;
}

void TestGetMinimumMaximum() {
    cout << "Testing Get Minimum and Get Maximum..." << endl;

    RedBlackTree rbt;

    bool minException = false;
    bool maxException = false;

    try {
        rbt.GetMin();
    }
    catch (const invalid_argument&) {
        minException = true;
    }

    try {
        rbt.GetMax();
    }
    catch (const invalid_argument&) {
        maxException = true;
    }

    assert(minException);
    assert(maxException);

    rbt.Insert(40);
    assert(rbt.GetMin() == 40);
    assert(rbt.GetMax() == 40);

    rbt.Insert(22);
    rbt.Insert(55);
    rbt.Insert(12);
    rbt.Insert(75);
    rbt.Insert(31);

    assert(rbt.GetMin() == 12);
    assert(rbt.GetMax() == 75);

    cout << "PASSED!" << endl << endl;
}

void TestDuplicateInsertion() {
    cout << "Testing Duplicate Insertion..." << endl;

    RedBlackTree rbt;
    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);

    bool exceptionThrown = false;

    try {
        rbt.Insert(10);
    }
    catch (const invalid_argument&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    assert(rbt.Size() == 3);
    assert(rbt.Contains(10));

    cout << "PASSED!" << endl << endl;
}

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

    TestToStrings();
    TestInsertRandomTests();

    TestCopyConstructor();
    TestContains();
    TestGetMinimumMaximum();
    TestDuplicateInsertion();

    TestPrivateTests();

    cout << "ALL TESTS PASSED!!" << endl;

    return 0;
}
