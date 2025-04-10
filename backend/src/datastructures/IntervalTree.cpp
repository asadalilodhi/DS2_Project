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
    if (node->right && start <= node->right->maxEnd) {
        queryHelper(node->right.get(), start, end, results);
    }
}

enum class CongestionLevel { FLUID = 0, LIGHT = 1, MODERATE = 2, HEAVY = 3, BLOCKED = 4 };

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