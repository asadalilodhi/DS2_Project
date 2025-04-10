#pragma once
#include <string>
// #include <chrono>
#include <vector>

// Congestion levels (also mentioned in proposal if anyone bothered reading it once)
enum class CongestionLevel { FLUID = 0, LIGHT = 1, MODERATE = 2, HEAVY = 3, BLOCKED = 4 };

// Extended traffic interval with metadata
struct TrafficInterval {
    // std::chrono::system_clock::time_point startTime;
    // std::chrono::system_clock::time_point endTime;
    double startTime;
    double endTime;
    int level;                 // 0=FLUID, 1=LIGHT, 2=MODERATE, 3=HEAVY, 4=BLOCKED
    std::string roadSegmentId;
    bool isEventRelated; // For "politician blockage" scenario
};

// Mock data generator for testing
std::vector<TrafficInterval> generateMockTrafficData();