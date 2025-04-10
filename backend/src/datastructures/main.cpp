#include <iostream>
#include "IntervalTree.hpp"
#include "TrafficData.hpp"
#include "Graph.hpp"

int main() {
    
    IntervalTree tree;

    std::vector<TrafficInterval> trafficData = generateMockTrafficData();

    for (const auto& interval : trafficData) {
        tree.insert(interval);
    }

    //------------------------------ Interval retreval --------------------------------------

    double queryStart, queryEnd;
    std::cout << "Enter the start time for the query (in military time): ";
    std::cin >> queryStart;
    std::cout << "Enter the end time for the query (in military time): ";
    std::cin >> queryEnd;

    std::vector<TrafficInterval> results = tree.queryOverlap(queryStart, queryEnd);

    std::cout << "Traffic conditions from " << queryStart << " to " << queryEnd << ":\n";
    for (const auto& interval : results) {
        std::cout << "Road: " << interval.roadSegmentId
                  << ", Start: " << interval.startTime
                  << ", End: " << interval.endTime
                  << ", Congestion: " << tree.congestionToString(static_cast<CongestionLevel>(interval.level))
                  << ", Event: " << (interval.isEventRelated ? "Yes" : "No") << std::endl;
    }

    //----------------------------------- Optimal route --------------------------------------------

    Graph roadNetwork;
    roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Korangi Road", 3, false); 
    roadNetwork.addRoadConnection("Korangi Road", "National Highway", 2, false);
    roadNetwork.addRoadConnection("Shahrah-e-Faisal", "M.A. Jinnah Road", 5, true);
    roadNetwork.addRoadConnection("National Highway", "M.A. Jinnah Road", 1, false);
    roadNetwork.addRoadConnection("M.A. Jinnah Road", "Khayaban-e-Iqbal", 4, false);
    roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Sindh High Court Road", 6, true); 
    roadNetwork.addRoadConnection("Shahrah-e-Faisal", "Shahrah-e-Quaideen", 3, false); 
    roadNetwork.addRoadConnection("Korangi Road", "Shahrah-e-Quaideen", 2, false); 
    roadNetwork.addRoadConnection("Shahrah-e-Quaideen", "Hassan Square Road", 3, false); 
    roadNetwork.addRoadConnection("Korangi Road", "Hassan Square Road", 5, true); 
    roadNetwork.addRoadConnection("Sindh High Court Road", "Karachi-Hyderabad Motorway", 4, false); 
    roadNetwork.addRoadConnection("Hassan Square Road", "National Highway", 2, true);

    roadNetwork.displayAllRoutes("Shahrah-e-Faisal", "Khayaban-e-Iqbal");

    return 0;
}
