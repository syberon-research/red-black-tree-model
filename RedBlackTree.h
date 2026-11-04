
#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>
#include <stdexcept>

#define COLOR_RED 0
#define COLOR_BLACK 1

using namespace std;

// Each node stores a value, its color, and links to its relatives.
struct RBTNode {
    int data;
    int color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    RBTNode(int value) {
        data = value;
        color = COLOR_RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
public:
    RedBlackTree();
    RedBlackTree(int value);
    RedBlackTree(const RedBlackTree& other);

    void Insert(int value);
    bool Contains(int value) const;

    int GetMin() const;
    int GetMax() const;

    unsigned long long int Size() const {
        return numItems;
    }

    string ToInfixString() const {
        return ToInfixString(root);
    }

    string ToPrefixString() const {
        return ToPrefixString(root);
    }

    string ToPostfixString() const {
        return ToPostfixString(root);
    }

    void PrivateTests();

private:
    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;

    string ToInfixString(RBTNode* n) const;
    string ToPrefixString(RBTNode* n) const;
    string ToPostfixString(RBTNode* n) const;

    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);

    void FixInsert(RBTNode* node);

    RBTNode* FindNode(int value) const;
    RBTNode* GetMinimumNode(RBTNode* node) const;
    RBTNode* GetMaximumNode(RBTNode* node) const;

    RBTNode* CopySubtree(RBTNode* node, RBTNode* parent);
};

#endif
