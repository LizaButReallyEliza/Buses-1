#ifndef ROUTINGENGINE_H
#define ROUTINGENGINE_H

#include "Graph.h"
#include <vector>

class RoutingEngine {
private:
    Graph& graph;
    std::vector<std::vector<int>> prevMatrix;

public:
    RoutingEngine(Graph& graph);

    void floydWarshall();

    std::vector<std::vector<int>> getPrevMatrix() const;

    unsigned int getDistance(unsigned int A, unsigned int B) const;
};

#endif // ROUTINGENGINE_H

