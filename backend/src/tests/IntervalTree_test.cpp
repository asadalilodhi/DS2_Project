#include "../datastructures/IntervalTree.hpp"
#include <cassert>
#include <iostream>

void printInterval(const TrafficInterval& interval) {
    std::cout << "Road: " << interval.roadSegmentId 
              << " | Time: [" << interval.startTime << " - " << interval.endTime << "]"
              << " | Level: " << interval.level 
              << " | Event: " << (interval.isEventRelated ? "Yes" : "No") << "\n";
}


void testInsertandBasicQuery(){
    IntervalTree t;
    std::cout << "Insertion test\n";

    TrafficInterval i1{.startTime = 10.0 , .endTime = 20.0,  .roadSegmentId = "Saddar Road", .level = 1 , .isEventRelated = false};
    t.insert(i1);

    std::cout << "Traversing [0.0 - 30.0] : \n";
    auto results = t.queryOverlap(0.0 , 30.0);

    for (const auto& interval : results) {
        printInterval(interval);
    }

    for (const auto& interval : results) {
        printInterval(interval);
    }

    // Test 2: Insert overlapping interval
    std::cout << "\n[Test 2] Inserting Shahrah-e-Faisal (15.0-25.0)\n";
    TrafficInterval i2{.startTime = 15.0 , .endTime = 25.0,  .roadSegmentId = "Shahrah-e-Faisal" , .level = 3 , .isEventRelated = true};
    t.insert(i2);

    std::cout << "Traversing [12.0 - 22.0] (Should show both roads):\n";
    results = t.queryOverlap(12.0, 22.0);
    for (const auto& interval : results) {
        printInterval(interval);
    }

    // Test 3: Insert non-overlapping interval
    std::cout << "\n[Test 3] Inserting University Road (30.0-40.0)\n";
    TrafficInterval i3{.startTime = 30.0, .endTime = 40.0,  .roadSegmentId = "University Road",  .level = 2, .isEventRelated = false};
    t.insert(i3);

    std::cout << "Traversing [5.0 - 35.0] (Should show all 3 roads):\n";
    results = t.queryOverlap(5.0, 35.0);
    for (const auto& interval : results) {
        printInterval(interval);
    }

    std::cout << "\n=== Test Complete ===\n";



}

void testOverlapQueries() {

}

void testEdgeCase() {

}

int main() {
    std::cout << "Interval Tree test";

    testInsertandBasicQuery();

    std::cout << "Test Done!! YAYYY";

    return 0;


}