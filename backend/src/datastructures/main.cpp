#include <iostream>
#include "IntervalTree.hpp"
#include "TrafficData.hpp"

int main() {
    // Step 1: Create the interval tree
    IntervalTree tree;

    // Step 2: Generate mock data
    std::vector<TrafficInterval> trafficData = generateMockTrafficData();

    // Step 3: Insert all intervals into the tree
    for (const auto& interval : trafficData) {
        tree.insert(interval);
    }

    // Step 4: Query for traffic conditions based on user input
    double queryStart, queryEnd;
    std::cout << "Enter the start time for the query (in military time): ";
    std::cin >> queryStart;
    std::cout << "Enter the end time for the query (in military time): ";
    std::cin >> queryEnd;

    // Step 5: Perform the query and get results
    std::vector<TrafficInterval> results = tree.queryOverlap(queryStart, queryEnd);

    // Step 6: Output the results
    std::cout << "Traffic conditions from " << queryStart << " to " << queryEnd << ":\n";
    for (const auto& interval : results) {
        std::cout << "Road: " << interval.roadSegmentId
                  << ", Start: " << interval.startTime
                  << ", End: " << interval.endTime
                  << ", Congestion: " << tree.congestionToString(static_cast<CongestionLevel>(interval.level))
                  << ", Event: " << (interval.isEventRelated ? "Yes" : "No") << std::endl;
    }

    return 0;
}
