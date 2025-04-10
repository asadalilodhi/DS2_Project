#include "IntervalTree.hpp"
#include <algorithm>

// Private helper function implementations
IntervalTree::Node* IntervalTree::insert(Node* node, Interval i) {
    if (node == nullptr) {
        return new Node(i);
    }

    // Using low value as the key for BST
    if (i.low < node->interval.low) {
        node->left = insert(node->left, i);
    } else {
        node->right = insert(node->right, i);
    }

    // Update the max value of this ancestor if needed
    node->max = std::max(node->max, i.high);
    return node;
}

bool IntervalTree::doOverlap(Interval i1, Interval i2) {
    return (i1.low <= i2.high && i2.low <= i1.high);
}

IntervalTree::Node* IntervalTree::search(Node* node, Interval i) {
    if (node == nullptr) {
        return nullptr;
    }

    // If intervals overlap, return this node
    if (doOverlap(node->interval, i)) {
        return node;
    }

    // If left child exists and its max is greater than i's low,
    // there may be an overlapping interval in the left subtree
    if (node->left != nullptr && node->left->max >= i.low) {
        return search(node->left, i);
    }

    // Otherwise, check the right subtree
    return search(node->right, i);
}

void IntervalTree::inorderTraversal(Node* node) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    std::cout << "[" << node->interval.low << ", " 
              << node->interval.high << "] max = " 
              << node->max << std::endl;
    inorderTraversal(node->right);
}

void IntervalTree::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Public interface implementations
void IntervalTree::insert(int low, int high) {
    if (low > high) {
        std::cout << "Invalid interval: low cannot be greater than high" << std::endl;
        return;
    }
    Interval i(low, high);
    root = insert(root, i);
}

bool IntervalTree::search(int low, int high) {
    if (low > high) {
        return false;
    }
    Interval i(low, high);
    return search(root, i) != nullptr;
}

void IntervalTree::printTree() {
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    inorderTraversal(root);
}