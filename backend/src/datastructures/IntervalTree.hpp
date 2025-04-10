#ifndef INTERVAL_TREE_HPP
#define INTERVAL_TREE_HPP

#include <iostream>

class IntervalTree {
private:
    struct Interval {
        int low;
        int high;
        Interval(int l = 0, int h = 0) : low(l), high(h) {}
    };

    struct Node {
        Interval interval;
        int max;
        Node* left;
        Node* right;
        Node(Interval i) : interval(i), max(i.high), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    Node* insert(Node* node, Interval i);
    bool doOverlap(Interval i1, Interval i2);
    Node* search(Node* node, Interval i);
    void inorderTraversal(Node* node);
    void destroyTree(Node* node);

public:
    IntervalTree() : root(nullptr) {}
    ~IntervalTree() {
        destroyTree(root);
    }

    // Public interface
    void insert(int low, int high);
    bool search(int low, int high);
    void printTree();
};

#endif // INTERVAL_TREE_HPP