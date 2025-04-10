#include "TrafficData.hpp"
#include <vector>
#include <string>

std::vector<TrafficInterval> generateMockTrafficData() {
    return {
        {800, 900, static_cast<int>(CongestionLevel::LIGHT),     "A1", false},
        {930, 1100, static_cast<int>(CongestionLevel::MODERATE),  "A1", true},
        {1000, 1130, static_cast<int>(CongestionLevel::HEAVY),     "B2", false},
        {1200, 1300, static_cast<int>(CongestionLevel::FLUID),     "C3", false},
        {1230, 1400, static_cast<int>(CongestionLevel::BLOCKED),   "B2", true},
        {1400, 1500, static_cast<int>(CongestionLevel::HEAVY),     "A1", false},
        {1430, 1600, static_cast<int>(CongestionLevel::MODERATE),  "C3", false},
        {1500, 1700, static_cast<int>(CongestionLevel::LIGHT),     "D4", false},
        {1530, 1800, static_cast<int>(CongestionLevel::HEAVY),     "B2", true},
        {1700, 1900, static_cast<int>(CongestionLevel::BLOCKED),   "A1", true},
        {1800, 2000, static_cast<int>(CongestionLevel::MODERATE),  "E5", false},
        {2000, 2130, static_cast<int>(CongestionLevel::LIGHT),     "C3", false},
        {2100, 2230, static_cast<int>(CongestionLevel::HEAVY),     "B2", true},
        {2200, 2300, static_cast<int>(CongestionLevel::BLOCKED),   "A1", true},
        {600, 730, static_cast<int>(CongestionLevel::FLUID),       "F6", false},
        {700, 830, static_cast<int>(CongestionLevel::LIGHT),       "G7", false},
        {845, 945, static_cast<int>(CongestionLevel::MODERATE),    "H8", true},
        {950, 1030, static_cast<int>(CongestionLevel::BLOCKED),    "F6", true},
        {1130, 1230, static_cast<int>(CongestionLevel::HEAVY),     "G7", false},
        {1330, 1430, static_cast<int>(CongestionLevel::LIGHT),     "H8", false},
        {1600, 1730, static_cast<int>(CongestionLevel::MODERATE),  "F6", true},
        {1730, 1830, static_cast<int>(CongestionLevel::BLOCKED),   "G7", true},
        {1900, 2030, static_cast<int>(CongestionLevel::HEAVY),     "H8", false},
        {2100, 2330, static_cast<int>(CongestionLevel::BLOCKED),   "F6", true}
    };
}