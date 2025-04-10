#include "Graph.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>

void Graph::addRoadConnection(const std::string& from, const std::string& to, double congestion, bool isEventRelated) {
    Road road = {to, congestion, isEventRelated};
    adjacencyList[from].push_back(road);
    road.roadId = from;  // Reverse road for undirected graph
    adjacencyList[to].push_back(road);
}

std::vector<std::string> Graph::dijkstra(const std::string& start, const std::string& end, double& totalWeight) {
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> pq;
    
    // Initialize distances
    for (const auto& pair : adjacencyList) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        std::string current = pq.top().second;
        pq.pop();

        for (const auto& road : adjacencyList[current]) {
            double alt = distances[current] + road.congestion;
            if (alt < distances[road.roadId]) {
                distances[road.roadId] = alt;
                previous[road.roadId] = current;
                pq.push({alt, road.roadId});
            }
        }
    }

    // Reconstruct the optimal path from start to end
    std::vector<std::string> path;
    std::string current = end;
    while (previous.find(current) != previous.end()) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // Calculate the total travel hours (weight) for this path
    totalWeight = distances[end];

    return path;
}

void Graph::displayAllRoutes(const std::string& start, const std::string& end) {
    // std::cout << "Displaying all possible routes from " << start << " to " << end << ":\n";

    // Call Dijkstra to get the best route
    double totalWeight;
    std::vector<std::string> optimalRoute = dijkstra(start, end, totalWeight);

    
    // This will just show the optimal route for now
    std::cout << "\nOptimal route from " << start << " to " << end << ":\n";
    for (const auto& road : optimalRoute) {
        std::cout << road << " ";
    }
    std::cout << "\nTotal Travel Hours: " << totalWeight << "\n";
}
