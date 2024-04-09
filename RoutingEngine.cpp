#include "RoutingEngine.h"

RoutingEngine::RoutingEngine(Graph& graph) : graph(graph) {}

void RoutingEngine::floydWarshall() {
    unsigned int N = graph.getSize();
    prevMatrix.assign(N, std::vector<int>(N, -1));

    for (unsigned int i = 0; i < N; ++i) {
        for (unsigned int j = 0; j < N; ++j) {
            if (graph.adjMatrix[i][j] != INF)
                prevMatrix[i][j] = i;
        }
    }

    for (unsigned int k = 0; k < N; ++k) {
        for (unsigned int i = 0; i < N; ++i) {
            for (unsigned int j = 0; j < N; ++j) {
                if (graph.adjMatrix[i][k] != INF && graph.adjMatrix[k][j] != INF && graph.adjMatrix[i][j] > graph.adjMatrix[i][k] + graph.adjMatrix[k][j]) {
                    graph.adjMatrix[i][j] = graph.adjMatrix[i][k] + graph.adjMatrix[k][j];
                    prevMatrix[i][j] = prevMatrix[k][j];
                }
            }
        }
    }
}

std::vector<std::vector<int>> RoutingEngine::getPrevMatrix() const {
    return prevMatrix;
}

unsigned int RoutingEngine::getDistance(unsigned int A, unsigned int B) const {
    return graph.adjMatrix[A][B];
}

