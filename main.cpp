#include "Graph.h"
#include "RoutingEngine.h"
#include "BusManager.h"
#include <iostream>

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

