#include "TrafficData.hpp"
#include <vector>
#include <string>

std::vector<TrafficInterval> generateMockTrafficData() {
    return {
        {800, 900, static_cast<int>(CongestionLevel::LIGHT),     "Shahrah-e-Faisal", false},
        {930, 1100, static_cast<int>(CongestionLevel::MODERATE),  "Shahrah-e-Faisal", true},
        {1000, 1130, static_cast<int>(CongestionLevel::HEAVY),     "Korangi Road", false},
        {1200, 1300, static_cast<int>(CongestionLevel::FLUID),     "National Highway", false},
        {1230, 1400, static_cast<int>(CongestionLevel::BLOCKED),   "Korangi Road", true},
        {1400, 1500, static_cast<int>(CongestionLevel::HEAVY),     "Shahrah-e-Faisal", false},
        {1430, 1600, static_cast<int>(CongestionLevel::MODERATE),  "M.A. Jinnah Road", false},
        {1500, 1700, static_cast<int>(CongestionLevel::LIGHT),     "Khayaban-e-Iqbal", false},
        {1530, 1800, static_cast<int>(CongestionLevel::HEAVY),     "Korangi Road", true},
        {1700, 1900, static_cast<int>(CongestionLevel::BLOCKED),   "Shahrah-e-Faisal", true},
        {1800, 2000, static_cast<int>(CongestionLevel::MODERATE),  "Karachi-Hyderabad Motorway", false},
        {2000, 2130, static_cast<int>(CongestionLevel::LIGHT),     "M.A. Jinnah Road", false},
        {2100, 2230, static_cast<int>(CongestionLevel::HEAVY),     "Korangi Road", true},
        {2200, 2300, static_cast<int>(CongestionLevel::BLOCKED),   "Shahrah-e-Faisal", true},
        {600, 730, static_cast<int>(CongestionLevel::FLUID),       "Hassan Square Road", false},
        {700, 830, static_cast<int>(CongestionLevel::LIGHT),       "Sindh High Court Road", false},
        {845, 945, static_cast<int>(CongestionLevel::MODERATE),    "Shahrah-e-Quaideen", true},
        {950, 1030, static_cast<int>(CongestionLevel::BLOCKED),    "Hassan Square Road", true},
        {1130, 1230, static_cast<int>(CongestionLevel::HEAVY),     "Sindh High Court Road", false},
        {1330, 1430, static_cast<int>(CongestionLevel::LIGHT),     "Shahrah-e-Quaideen", false},
        {1600, 1730, static_cast<int>(CongestionLevel::MODERATE),  "Hassan Square Road", true},
        {1730, 1830, static_cast<int>(CongestionLevel::BLOCKED),   "Sindh High Court Road", true},
        {1900, 2030, static_cast<int>(CongestionLevel::HEAVY),     "Shahrah-e-Quaideen", false},
        {2100, 2330, static_cast<int>(CongestionLevel::BLOCKED),   "Hassan Square Road", true}
    };
}

