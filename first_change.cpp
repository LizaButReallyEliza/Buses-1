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

void printPath(unsigned int start, unsigned int end, const std::vector<int>& prev, const std::vector<std::vector<unsigned int>>& dist) {
    if (prev[end] == -1) {
        std::cout << "There is no path for this bus from " << start << " to " << end << std::endl;
        return;
    }

    std::cout << "Path for bus from " << start << " to " << end << ": ";
    std::vector<unsigned int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    
    for (unsigned int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nShortest distance: " << dist[start][end] << std::endl;
}

//Complexity of this part must be O(N^2 + M), but I couldn't achieve it
std::vector<int> dijkstra(unsigned int start, unsigned int end, const std::vector<std::vector<unsigned int>>& graph) {
    unsigned int n = graph.size();
    std::vector<unsigned int> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

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
            if (graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]) {
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
    unsigned int A, B, weight;
    unsigned int busNumber;
    while (std::cin >> operation) {
        if (operation == "add_bus") {
            std::cin >> A >> B;
            std::vector<int> prev = dijkstra(A, B, dist);
            std::cout << dist[A][B] << std::endl;
        } else if (operation == "construct_street") {
            std::cin >> A >> B >> weight;
            addStreet(A, B, weight, dist);
        } else if (operation == "details") {
            std::cin >> busNumber >> A >> B;
            if (busNumber >= N) {
                std::cout << "Invalid bus number." << std::endl;
                continue;
            }
            std::vector<int> prev = dijkstra(A, B, dist);
printPath(A, B, prev, dist);
        } else {
            std::cout << "Invalid operation." << std::endl;
            break;
        }
    }

    return 0;
}

//example
// 5 6
// 0 1 10
// 0 2 15
// 1 2 5
// 1 3 20
// 3 4 5
// 2 3 10
//add_bus 0 4 (output 30)
//construct_street 2 4 1 (2 and 4 are vertices, 1 - weight)
//details 0 0 4 (output must be shortest path for bus 0 from 0 to 4: 2 3)
