// #include "Graph.hpp"
// #include <queue>
// #include <unordered_map>
// #include <iostream>
// #include <vector>
// #include <algorithm>

// void Graph::addRoadConnection(const std::string& from, const std::string& to, double congestion, bool isEventRelated) {
//     Road road = {to, congestion, isEventRelated};
//     adjacencyList[from].push_back(road);
//     road.roadId = from;  // Reverse road for undirected graph
//     adjacencyList[to].push_back(road);
// }

// std::vector<std::string> Graph::dijkstra(const std::string& start, const std::string& end, double& totalWeight) {
//     std::unordered_map<std::string, double> distances;
//     std::unordered_map<std::string, std::string> previous;
//     std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> pq;
    
//     // Initialize distances
//     for (const auto& pair : adjacencyList) {
//         distances[pair.first] = std::numeric_limits<double>::infinity();
//     }
//     distances[start] = 0;
//     pq.push({0, start});

//     while (!pq.empty()) {
//         std::string current = pq.top().second;
//         pq.pop();

//         for (const auto& road : adjacencyList[current]) {
//             double alt = distances[current] + road.congestion;
//             if (alt < distances[road.roadId]) {
//                 distances[road.roadId] = alt;
//                 previous[road.roadId] = current;
//                 pq.push({alt, road.roadId});
//             }
//         }
//     }

//     // Reconstruct the optimal path from start to end
//     std::vector<std::string> path;
//     std::string current = end;
//     while (previous.find(current) != previous.end()) {
//         path.push_back(current);
//         current = previous[current];
//     }
//     path.push_back(start);
//     std::reverse(path.begin(), path.end());

//     // Calculate the total travel hours (weight) for this path
//     totalWeight = distances[end];

//     return path;
// }

// void Graph::displayAllRoutes(const std::string& start, const std::string& end) {
//     // std::cout << "Displaying all possible routes from " << start << " to " << end << ":\n";

//     // Call Dijkstra to get the best route
//     double totalWeight;
//     std::vector<std::string> optimalRoute = dijkstra(start, end, totalWeight);

    
//     // This will just show the optimal route for now
//     std::cout << "\nOptimal route from " << start << " to " << end << ":\n";
//     for (const auto& road : optimalRoute) {
//         std::cout << road << " ";
//     }
//     std::cout << "\nTotal Travel Hours: " << totalWeight << "\n";
// }
#include "Graph.hpp"
#include "IntervalTree.hpp"   // for dijkstraWithTime
#include <queue>
#include <unordered_map>
#include <iostream>           // <<--- needed for std::cout
#include <limits>             // for std::numeric_limits<double>::infinity()
#include <algorithm>          // for std::reverse
#include <vector>

// Adds a bidirectional edge from→to with a unique roadId, baseCost, and optional event flag
void Graph::addRoadConnection(const std::string& from,
                              const std::string& to,
                              double baseCost,
                              bool isEventRoad)
{
    static int edgeCounter = 0;
    // Unique ID: "from→to#N"
    std::string rid = from + "→" + to + "#" + std::to_string(edgeCounter++);

    // Forward edge
    Road roadFwd{ to, baseCost, isEventRoad, rid };
    adjacencyList[from].push_back(roadFwd);

    // Reverse edge (undirected)
    Road roadRev{ from, baseCost, isEventRoad, rid };
    adjacencyList[to].push_back(roadRev);
}

// Standard Dijkstra (ignores time/interval tree)
std::vector<std::string> Graph::dijkstra(const std::string& start,
                                         const std::string& end,
                                         double& totalWeight)
{
    using PD = std::pair<double,std::string>;
    std::priority_queue<PD,std::vector<PD>,std::greater<PD>> pq;
    std::unordered_map<std::string,double> dist;
    std::unordered_map<std::string,std::string> prev;

    // Initialize distances
    for (auto& kv : adjacencyList) {
        dist[kv.first] = std::numeric_limits<double>::infinity();
    }
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& road : adjacencyList[u]) {
            double alt = dist[u] + road.baseCost;
            if (alt < dist[road.toNode]) {
                dist[road.toNode] = alt;
                prev[road.toNode] = u;
                pq.push({alt, road.toNode});
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    for (std::string at = end; prev.count(at); at = prev[at]) 
        path.push_back(at);
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    totalWeight = dist[end];
    return path;
}

void Graph::displayAllRoutes(const std::string& start,
                             const std::string& end)
{
    double totalWeight;
    auto optimalRoute = dijkstra(start, end, totalWeight);

    std::cout << "\nOptimal route from " << start
              << " to " << end << ":\n";
    for (auto& node : optimalRoute)
        std::cout << node << " ";
    std::cout << "\nTotal Travel Hours: " << totalWeight << "\n";
}

// Time-aware Dijkstra: applies interval-tree penalties at departureTime
std::vector<std::string> Graph::dijkstraWithTime(
    const std::string& start,
    const std::string& end,
    double departureTime,
    const IntervalTree& tree,
    double& totalCost)
{
    using PD = std::pair<double,std::string>;
    std::priority_queue<PD,std::vector<PD>,std::greater<PD>> pq;
    std::unordered_map<std::string,double> dist;
    std::unordered_map<std::string,std::string> prev;

    // Initialize
    for (auto& kv : adjacencyList) {
        dist[kv.first] = std::numeric_limits<double>::infinity();
    }
    dist[start] = 0;
    pq.push({0, start});

    // Main loop
    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (u == end) break;

        for (auto& road : adjacencyList[u]) {
            double cost = road.baseCost;

            // Query congestion intervals for this exact departureTime
            auto overlaps = tree.queryOverlap(departureTime, departureTime);
            for (auto& iv : overlaps) {
                if (iv.roadSegmentId == road.roadId) {
                    cost += (iv.level + 1) * 0.5;  // penalty factor
                    break;
                }
            }

            double alt = dist[u] + cost;
            if (alt < dist[road.toNode]) {
                dist[road.toNode] = alt;
                prev[road.toNode] = u;
                pq.push({alt, road.toNode});
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    for (std::string at = end; prev.count(at); at = prev[at]) 
        path.push_back(at);
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    totalCost = dist[end];
    return path;
}
