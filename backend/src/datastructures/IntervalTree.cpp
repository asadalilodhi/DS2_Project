#include "IntervalTree.hpp"
#include <algorithm>
#include <iostream>
#include <string>

void IntervalTree::insertHelper(std::unique_ptr<Node>& node, const TrafficInterval& interval) {
    if (!node) {
        node = std::make_unique<Node>(interval);
    } else if (interval.startTime < node->interval.startTime) {
        insertHelper(node->left, interval);  // Recursive call
    } else {
        insertHelper(node->right, interval);
    }
    node->maxEnd = std::max({node->interval.endTime,
                            node->left ? node->left->maxEnd : 0,
                            node->right ? node->right->maxEnd : 0});
}

void IntervalTree::insert(const TrafficInterval& interval) {
    insertHelper(root, interval);
}

std::vector<TrafficInterval> IntervalTree::queryOverlap(double start, double end) const {
    std::vector<TrafficInterval> results;
    queryHelper(root.get(), start, end, results);
    return results;
}

void IntervalTree::queryHelper(const Node* node, double start, double end, 
                             std::vector<TrafficInterval>& results) const {
    if (!node) return;
    if (start <= node->interval.endTime && end >= node->interval.startTime) {
        results.push_back(node->interval);
    }
    if (node->left && start <= node->left->maxEnd) {
        queryHelper(node->left.get(), start, end, results);
    }
    if (node->right && end >= node->interval.startTime) {  // fixed condition
        queryHelper(node->right.get(), start, end, results);
    }
}

void IntervalTree::clear() {
    root.reset();  // Clear the whole tree
}

std::string IntervalTree::congestionToString(CongestionLevel level) {
    switch (level) {
        case CongestionLevel::FLUID:    return "FLUID";
        case CongestionLevel::LIGHT:    return "LIGHT";
        case CongestionLevel::MODERATE: return "MODERATE";
        case CongestionLevel::HEAVY:    return "HEAVY";
        case CongestionLevel::BLOCKED:  return "BLOCKED";
        default:                        return "UNKNOWN";
    }
}


void IntervalTree::printTree() const {
    printTreeHelper(root);
}

void IntervalTree::printTreeHelper(const std::unique_ptr<Node>& node, int depth) const {
    if (!node) return;

    printTreeHelper(node->right, depth + 1);

    std::cout << std::string(depth * 4, ' ') << "Interval: [" << node->interval.startTime << ", " 
              << node->interval.endTime << "], MaxEnd: " << node->maxEnd 
              << ", Road: " << node->interval.roadSegmentId << "\n";


    printTreeHelper(node->left, depth + 1);
}