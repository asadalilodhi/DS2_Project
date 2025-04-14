#include "datastructures/IntervalTree.hpp"
#include "datastructures/TrafficData.hpp"
#include <iostream>

std::string getCongestionName(int level) {
    const std::vector<std::string> names = {"FLUID", "LIGHT", "MODERATE", "HEAVY", "BLOCKED"};
    return (level >= 0 && level < static_cast<int>(names.size())) ? names[level] : "UNKNOWN";
}

int main() {
    IntervalTree tree;
    
    // Query overlapping intervals (2PM-4PM)
    auto congestedRoads = tree.queryOverlap(1710007200, 1710014400);

    // Print each congested road with its level name
    for (const auto& interval : congestedRoads) {
        std::cout << "Congestion on " << interval.roadSegmentId << " (Level " << interval.level << " - " << getCongestionName(interval.level) << ")\n";
    }
    
    return 0;
}