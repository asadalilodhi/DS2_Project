// #include <iostream>
// #include "IntervalTree.hpp"
// #include "TrafficData.hpp"
// #include "Graph.hpp"

// int main() {
    
//     IntervalTree tree;

//     std::vector<TrafficInterval> trafficData = generateMockTrafficData();

//     for (const auto& interval : trafficData) {
//         tree.insert(interval);
//     }
//     tree.printTree();

//     //------------------------------ Interval retreval --------------------------------------

//     double queryStart, queryEnd;
//     std::cout << "Enter the start time for the query (in military time): ";
//     std::cin >> queryStart;
//     std::cout << "Enter the end time for the query (in military time): ";
//     std::cin >> queryEnd;

//     std::vector<TrafficInterval> results = tree.queryOverlap(queryStart, queryEnd);

//     std::cout << "Traffic conditions from " << queryStart << " to " << queryEnd << ":\n";
//     for (const auto& interval : results) {
//         std::cout << "Road: " << interval.roadSegmentId
//                   << ", Start: " << interval.startTime
//                   << ", End: " << interval.endTime
//                   << ", Congestion: " << tree.congestionToString(static_cast<CongestionLevel>(interval.level))
//                   << ", Event: " << (interval.isEventRelated ? "Yes" : "No") << std::endl;
//     }

//     //----------------------------------- Optimal route --------------------------------------------

//     Graph roadNetwork;
//     roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Korangi Road", 3, false); 
//     roadNetwork.addRoadConnection("Korangi Road", "National Highway", 2, false);
//     roadNetwork.addRoadConnection("Shahrah-e-Faisal", "M.A. Jinnah Road", 5, true);
//     roadNetwork.addRoadConnection("National Highway", "M.A. Jinnah Road", 1, false);
//     roadNetwork.addRoadConnection("M.A. Jinnah Road", "Khayaban-e-Iqbal", 4, false);
//     roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Sindh High Court Road", 6, true); 
//     roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Shahrah-e-Quaideen", 3, false); 
//     roadNetwork.addRoadConnection("Korangi Road", "Shahrah-e-Quaideen", 2, false); 
//     roadNetwork.addRoadConnection("Shahrah-e-Quaideen", "Hassan Square Road", 3, false); 
//     roadNetwork.addRoadConnection("Korangi Road", "Hassan Square Road", 5, true); 
//     roadNetwork.addRoadConnection("Sindh High Court Road", "Karachi-Hyderabad Motorway", 4, false); 
//     roadNetwork.addRoadConnection("Hassan Square Road", "National Highway", 2, true);

//     roadNetwork.displayAllRoutes("Shahrah-e-Faisal", "Khayaban-e-Iqbal");

//     return 0;
// }
#include <iostream>
#include "IntervalTree.hpp"
#include "TrafficData.hpp"
#include "Graph.hpp"

int main() {
    // 1) Build the interval tree with mock traffic intervals
    IntervalTree tree;
    auto trafficData = generateMockTrafficData();
    for (const auto& iv : trafficData) {
        tree.insert(iv);
    }
    // Optional: visualize your tree
    // tree.printTree();

    // 2) Build your static graph of A→B (or real Karachi roads)
    Graph roadNetwork;
    // Four alternative routes between A and B
    roadNetwork.addRoadConnection("A", "B", 5.0, false);
    roadNetwork.addRoadConnection("A", "B", 6.2, true);
    roadNetwork.addRoadConnection("A", "B", 4.5, false);
    roadNetwork.addRoadConnection("A", "B", 5.8, false);
    // (If desired, other nodes/edges can be added here)

    // 3) Ask user for a departure time
    double departureTime;
    std::cout << "Enter departure time (e.g. 8.25 for 08:15): ";
    std::cin >> departureTime;

    // 4) Compute the best path A→B at the given time
    double totalCost;
    auto bestPath = roadNetwork.dijkstraWithTime(
                        "A", "B",
                        departureTime,
                        tree,
                        totalCost);

    // 5) Print the result
    std::cout << "\nBest path from A to B at " << departureTime << ":\n";
    for (auto& node : bestPath) {
        std::cout << node << " -> ";
    }
    std::cout << "\nTotal cost (with congestion): "
              << totalCost << "\n";

    return 0;
}
