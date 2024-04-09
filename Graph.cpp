#include "Graph.h"

Graph::Graph(unsigned int N) : adjMatrix(N, std::vector<unsigned int>(N, INF)) {
    for (unsigned int i = 0; i < N; ++i) {
        adjMatrix[i][i] = 0;
    }
}

void Graph::addStreet(unsigned int A, unsigned int B, unsigned int weight) {
    adjMatrix[A][B] = weight;
    adjMatrix[B][A] = weight;
}

unsigned int Graph::getSize() const {
    return adjMatrix.size();
}

