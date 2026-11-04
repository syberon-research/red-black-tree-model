
#include "RedBlackTree.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

// Empty tree constructor.
RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

// Constructor containing one node.
RedBlackTree::RedBlackTree(int value) {
    root = new RBTNode(value);
    root->color = COLOR_BLACK;
    numItems = 1;
}

// Deep-copy constructor.
RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    root = CopySubtree(other.root, nullptr);
    numItems = other.numItems;
}

// Recursively copy a subtree while preserving its structure and colors.
RBTNode* RedBlackTree::CopySubtree(RBTNode* node, RBTNode* parent) {
    if (node == nullptr) {
        return nullptr;
    }

    RBTNode* copy = new RBTNode(node->data);
    copy->color = node->color;
    copy->parent = parent;

    copy->left = CopySubtree(node->left, copy);
    copy->right = CopySubtree(node->right, copy);

    return copy;
}

// Return the node containing the requested value.
RBTNode* RedBlackTree::FindNode(int value) const {
    RBTNode* current = root;

    while (current != nullptr) {
        if (value == current->data) {
            return current;
        }

        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

// Search for a value.
bool RedBlackTree::Contains(int value) const {
    return FindNode(value) != nullptr;
}

// Left rotation around a node.
void RedBlackTree::RotateLeft(RBTNode* node) {
    RBTNode* rightChild = node->right;

    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

// Right rotation around a node.
void RedBlackTree::RotateRight(RBTNode* node) {
    RBTNode* leftChild = node->left;

    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

// Restore red-black properties after insertion.
void RedBlackTree::FixInsert(RBTNode* node) {
    while (node != root &&
           node->parent->color == COLOR_RED) {

        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBTNode* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    RotateLeft(node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateRight(grandparent);
            }
        } else {
            RBTNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    RotateRight(node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateLeft(grandparent);
            }
        }
    }

    root->color = COLOR_BLACK;
}

// Insert a new integer into the tree.
void RedBlackTree::Insert(int value) {
    RBTNode* parent = nullptr;
    RBTNode* current = root;

    // Find the insertion position and check for duplicates.
    while (current != nullptr) {
        parent = current;

        if (value == current->data) {
            throw invalid_argument("Duplicate value");
        }

        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Create and attach the new node.
    RBTNode* newNode = new RBTNode(value);
    newNode->parent = parent;

    if (parent == nullptr) {
        root = newNode;
    } else if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    numItems++;
    FixInsert(newNode);
}

// Find the smallest node in a subtree.
RBTNode* RedBlackTree::GetMinimumNode(RBTNode* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

// Find the largest node in a subtree.
RBTNode* RedBlackTree::GetMaximumNode(RBTNode* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->right != nullptr) {
        node = node->right;
    }

    return node;
}

// Return the minimum integer.
int RedBlackTree::GetMin() const {
    if (root == nullptr) {
        throw invalid_argument("Cannot get minimum of an empty tree.");
    }

    return GetMinimumNode(root)->data;
}

// Return the maximum integer.
int RedBlackTree::GetMax() const {
    if (root == nullptr) {
        throw invalid_argument("Cannot get maximum of an empty tree.");
    }

    return GetMaximumNode(root)->data;
}

// Infix: left, root, right.
string RedBlackTree::ToInfixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result = ToInfixString(n->left);

    result += " ";
    result += (n->color == COLOR_RED ? "R" : "B");
    result += to_string(n->data);
    result += " ";

    result += ToInfixString(n->right);

    return result;
}

// Prefix: root, left, right.
string RedBlackTree::ToPrefixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result;
    result += " ";
    result += (n->color == COLOR_RED ? "R" : "B");
    result += to_string(n->data);
    result += " ";

    result += ToPrefixString(n->left);
    result += ToPrefixString(n->right);

    return result;
}

// Postfix: left, right, root.
string RedBlackTree::ToPostfixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result = ToPostfixString(n->left);
    result += ToPostfixString(n->right);

    result += " ";
    result += (n->color == COLOR_RED ? "R" : "B");
    result += to_string(n->data);
    result += " ";

    return result;
}

// Basic internal tests.
void RedBlackTree::PrivateTests() {
    assert(root == nullptr || root->color == COLOR_BLACK);

    RedBlackTree test;
    test.Insert(10);
    test.Insert(5);
    test.Insert(15);

    assert(test.Contains(10));
    assert(test.Contains(5));
    assert(test.Contains(15));
    assert(!test.Contains(20));

    assert(test.GetMin() == 5);
    assert(test.GetMax() == 15);
    assert(test.Size() == 3);
}
