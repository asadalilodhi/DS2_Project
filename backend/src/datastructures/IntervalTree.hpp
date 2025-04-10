#ifndef INTERVAL_TREE_HPP
#define INTERVAL_TREE_HPP

#include <iostream>

#pragma once
#include <vector>
#include <memory>
#include "TrafficData.hpp" 



class IntervalTree {
private:

    struct Node {
        TrafficInterval interval;
        double maxEnd;  // Max end time in subtree + used in comparisions
        std::unique_ptr<Node> left, right;
        Node(const TrafficInterval& i) 
            : interval(i), maxEnd(i.endTime), left(nullptr), right(nullptr) {}
    };
    void insertHelper(std::unique_ptr<Node>& node, const TrafficInterval& interval);
    void queryHelper(const Node* node, double start, double end, std::vector<TrafficInterval>& results) const ;
    
    std::unique_ptr<Node> root;

public:
    void insert(const TrafficInterval& interval);
    std::vector<TrafficInterval> queryOverlap(double start, double end) const;
    std::string congestionToString(CongestionLevel level);
    void clear();
};

#endif // INTERVAL_TREE_HPP