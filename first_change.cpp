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

public:
    RoutingEngine(Graph& graph) : graph(graph) {}

    void floydWarshall() {
        unsigned int N = graph.getSize();
        for (unsigned int k = 0; k < N; ++k) {
            for (unsigned int i = 0; i < N; ++i) {
                for (unsigned int j = 0; j < N; ++j) {
                    if (graph.adjMatrix[i][k] != INF && graph.adjMatrix[k][j] != INF) {
                        graph.adjMatrix[i][j] = std::min(graph.adjMatrix[i][j], graph.adjMatrix[i][k] + graph.adjMatrix[k][j]);
                    }
                }
            }
        }
    }

    void addStreetAndUpdatePaths(unsigned int A, unsigned int B, unsigned int weight) {
        graph.addStreet(A, B, weight);
        floydWarshall();
    }

    std::vector<int> dijkstra(unsigned int start, unsigned int end) {
        unsigned int n = graph.getSize();
        std::vector<unsigned int> dist(n, INF);
        std::vector<int> prev(n, -1);
        std::priority_queue<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>, std::greater<>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (dist[u] < cost) continue;

            for (unsigned int v = 0; v < n; ++v) {
                if (graph.adjMatrix[u][v] != INF) {
                    unsigned int alt = dist[u] + graph.adjMatrix[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        return prev;
    }

    unsigned int getDistance(unsigned int A, unsigned int B) const {
        return graph.adjMatrix[A][B];
    }
};


class BusManager {
private:
    RoutingEngine& engine;

public:
    BusManager(RoutingEngine& engine) : engine(engine) {}

    void addBus(unsigned int A, unsigned int B) {
        std::cout << "Shortest path distance from " << A << " to " << B << ": " << engine.getDistance(A, B) << std::endl;
    }

    void printDetails(unsigned int A, unsigned int B) {
    auto prev = engine.dijkstra(A, B);
    if (prev[B] == -1) {
        std::cout << "No path exists from " << A << " to " << B << std::endl;
        return;
    }

    std::vector<unsigned int> path;
    for (int at = B; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Path from " << A << " to " << B << ": ";
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
    BusManager busManager(engine);

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "add_bus") {
            unsigned int A, B;
            std::cin >> A >> B;
            busManager.addBus(A, B);
        } else if (operation == "construct_street") {
            unsigned int A, B, weight;
            std::cin >> A >> B >> weight;
            engine.addStreetAndUpdatePaths(A, B, weight);
            std::cout << "Street constructed and paths updated.\n";
        } else if (operation == "details") {
            unsigned int busNumber, A, B;
            std::cin >> busNumber >> A >> B;
            busManager.printDetails(A, B);
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
