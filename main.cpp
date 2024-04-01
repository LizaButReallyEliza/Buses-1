#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const unsigned int INF = std::numeric_limits<unsigned int>::max();

void floydWarshall(std::vector<std::vector<unsigned int>>& dist) {
    unsigned int N = dist.size();
    for (unsigned int k = 0; k < N; ++k) {
        for (unsigned int i = 0; i < N; ++i) {
            for (unsigned int j = 0; j < N; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void addStreet(unsigned int A, unsigned int B, unsigned int weight, std::vector<std::vector<unsigned int>>& dist) {
    dist[A][B] = dist[B][A] = weight;
    unsigned int N = dist.size();
    
    for (unsigned int i = 0; i < N; ++i) {
        for (unsigned int j = 0; j < N; ++j) {
            if (dist[i][j] <= weight) {
                dist[i][j] = std::min(dist[i][j], dist[i][A] + weight + dist[B][j]);
                dist[j][i] = dist[i][j];
            }
        }
    }
}

void printPath(unsigned int start, unsigned int end, const std::vector<int>& prev) {
    if (prev[end] == -1) {
        std::cout << "There is no path for this bus from " << start << " to " << end << std::endl;
        return;
    }

    std::cout << "Path for bus from " << start << " to " << end << ": ";
    std::vector<unsigned int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> dijkstra(unsigned int start, unsigned int end, const std::vector<std::vector<unsigned int>>& graph) {
    unsigned int n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<unsigned int> dist(n, INF);
    std::vector<int> prev(n, -1);

    dist[start] = 0;
    std::priority_queue<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>,
    std::greater<std::pair<unsigned int, unsigned int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        unsigned int u = pq.top().second;
        pq.pop();

        if (u == end) break;
        if (visited[u]) continue;
        visited[u] = true;

        for (unsigned int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return prev;
}

int main() {
    unsigned int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<unsigned int>> dist(N, std::vector<unsigned int>(N, INF));
    for (unsigned int i = 0; i < M; ++i) {
        unsigned int u, v, k;
        std::cin >> u >> v >> k;
        dist[u][v] = dist[v][u] = k;
    }

    floydWarshall(dist);

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "add_bus") {
            unsigned int A, B;
            std::cin >> A >> B;
            std::vector<int> prev = dijkstra(A, B, dist);
            std::cout << dist[A][B] << std::endl;
        } else if (operation == "construct_street") {
            unsigned int A, B, weight;
            std::cin >> A >> B >> weight;
            addStreet(A, B, weight, dist);
        } else if (operation == "details") {
            unsigned int busNumber, A, B;
            std::cin >> busNumber >> A >> B;
            if (busNumber >= N) {
                std::cout << "Invalid bus number." << std::endl;
                continue;
            }
            std::vector<int> prev = dijkstra(A, B, dist);
            printPath(A, B, prev);
        } else {
            std::cout << "Invalid operation." << std::endl;
        }
    }

    return 0;
}
