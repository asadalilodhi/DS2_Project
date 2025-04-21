#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include "TrafficData.hpp"
#include "IntervalTree.hpp"


// struct Road {
//     std::string roadId;
//     double congestion;  // Congestion level (weight)
//     bool isEventRelated; // Is there an event causing the congestion?
// };
struct Road {
    std::string toNode;      // Destination node ID ("B", "Saddar", etc)
    double      baseCost;    // Static cost (distance or travel time)
    bool        isEventRoad; // Event flag (optional)
    std::string roadId;      // Unique edge ID (so IntervalTree can match it)
     };

class Graph {
    public:
   
       // from → to with a given baseCost and optional event flag
       void addRoadConnection(const std::string& from,
                              const std::string& to,
                              double baseCost,
                              bool isEventRoad);
   
       // Standard Dijkstra (no time‑based penalties)
       std::vector<std::string> dijkstra(const std::string& start,
                                         const std::string& end,
                                         double& totalWeight);
   
       void displayAllRoutes(const std::string& start, const std::string& end);
   
       // Time‑aware Dijkstra: applies IntervalTree penalties at departureTime
       std::vector<std::string> dijkstraWithTime(
           const std::string& start,
           const std::string& end,
           double departureTime,
           const IntervalTree& tree,
           double& totalCost
       );
    
private:
    std::unordered_map<std::string, std::vector<Road>> adjacencyList;
};
