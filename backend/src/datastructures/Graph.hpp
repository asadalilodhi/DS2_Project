#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include "TrafficData.hpp"

struct Road {
    std::string roadId;
    double congestion;  // Congestion level (weight)
    bool isEventRelated; // Is there an event causing the congestion?
};

class Graph {
public:
    void addRoadConnection(const std::string& from, const std::string& to, double congestion, bool isEventRelated);
    std::vector<std::string> dijkstra(const std::string& start, const std::string& end, double& totalWeight);
    void displayAllRoutes(const std::string& start, const std::string& end);
    
private:
    std::unordered_map<std::string, std::vector<Road>> adjacencyList;
};
