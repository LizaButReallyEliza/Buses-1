#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

const unsigned int INF = std::numeric_limits<unsigned int>::max();

class Graph {
public:
    std::vector<std::vector<unsigned int>> adjMatrix;

    Graph(unsigned int N) : adjMatrix(N, std::vector<unsigned int>(N, INF)) {
        for (unsigned int i = 0; i < N; ++i) {
            adjMatrix[i][i] = 0;
        }
    }

    void addStreet(unsigned int A, unsigned int B, unsigned int weight) {
        adjMatrix[A][B] = weight;
        adjMatrix[B][A] = weight;
    }

    unsigned int getSize() const {
        return adjMatrix.size();
    }
};

class RoutingEngine {
private:
    Graph& graph;
    std::vector<std::vector<int>> prevMatrix;

public:
    RoutingEngine(Graph& graph) : graph(graph) {}

    void floydWarshall() {
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

    std::vector<std::vector<int>> getPrevMatrix() const {
        return prevMatrix;
    }

    unsigned int getDistance(unsigned int A, unsigned int B) const {
        return graph.adjMatrix[A][B];
    }
};



class BusManager {
private:
    RoutingEngine& engine;
    unsigned int graphSize;

public:
    BusManager(RoutingEngine& engine, unsigned int graphSize) : engine(engine), graphSize(graphSize) {}

    void addBus(unsigned int A, unsigned int B) {
        std::cout << "Shortest path distance from " << A << " to " << B << ": " << engine.getDistance(A, B) << std::endl;
    }

    void printDetails(unsigned int busNumber, unsigned int A, unsigned int B) {
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

};

int main() {
    unsigned int N, M;
    std::cin >> N >> M;

    Graph graph(N);
    RoutingEngine engine(graph);
    for (unsigned int i = 0; i < M; ++i) {
        unsigned int u, v, k;
        std::cin >> u >> v >> k;
        graph.addStreet(u, v, k);
    }

    engine.floydWarshall();
    BusManager busManager(engine, graph.getSize());

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "add_bus") {
            unsigned int A, B;
            std::cin >> A >> B;
            busManager.addBus(A, B);
        } else if (operation == "construct_street") {
            unsigned int A, B, weight;
            std::cin >> A >> B >> weight;
            graph.addStreet(A, B, weight);
            engine.floydWarshall();
            std::cout << "Street constructed and paths updated.\n";
        } else if (operation == "details") {
            unsigned int busNumber, A, B;
            std::cin >> busNumber >> A >> B;
            busManager.printDetails(busNumber, A, B);
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}

//example
// 5 6
// 0 1 5
// 0 2 3
// 1 2 2
// 1 3 6
// 2 3 7
// 3 4 4
// add_bus 0 4
// (Output) Shortest path distance from 0 to 4: 14
// construct_street 2 4 5
// (Output) Street constructed and paths updated.
// details 1 0 4
// (Output) Shortest path for bus 1 from 0 to 4: 0 -> 2 -> 4
