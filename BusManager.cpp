#include "BusManager.h"
#include <algorithm>

BusManager::BusManager(RoutingEngine& engine, unsigned int graphSize) : engine(engine), graphSize(graphSize) {}

void BusManager::addBus(unsigned int A, unsigned int B) {
    std::cout << "Shortest path distance from " << A << " to " << B << ": " << engine.getDistance(A, B) << std::endl;
}

void BusManager::printDetails(unsigned int busNumber, unsigned int A, unsigned int B) {
    auto prevMatrix = engine.getPrevMatrix();
    if (prevMatrix[A][B] == -1) {
        std::cout << "No path exists from " << A << " to " << B << std::endl;
        return;
    }

    std::vector<unsigned int> path;
    for (int at = B; at != A; at = prevMatrix[A][at]) {
        path.push_back(at);
    }
    path.push_back(A);
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest path for bus " << busNumber << " from " << A << " to " << B << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

