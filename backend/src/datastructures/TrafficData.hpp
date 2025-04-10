#pragma once

#include <string>
#include <vector>

// Levels of congestion, aligned with proposal
enum class CongestionLevel {
    FLUID = 0,
    LIGHT = 1,
    MODERATE = 2,
    HEAVY = 3,
    BLOCKED = 4
};

// Struct representing one time-based traffic data point
struct TrafficInterval {
    double startTime;          // Start of interval in military time (e.g. 1700 = 5 PM)
    double endTime;            // End of interval in military time
    int level;                 // Congestion level (stored as int for tree compatibility)
    std::string roadSegmentId; // Road or segment name
    bool isEventRelated;       // True if caused by a special event or politician blocking
};

// Generates mock traffic data to populate the interval tree
std::vector<TrafficInterval> generateMockTrafficData();