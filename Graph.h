#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>

const unsigned int INF = std::numeric_limits<unsigned int>::max();

class Graph {
public:
    std::vector<std::vector<unsigned int>> adjMatrix;

    Graph(unsigned int N);

    void addStreet(unsigned int A, unsigned int B, unsigned int weight);

    unsigned int getSize() const;
};

#endif // GRAPH_H

