#ifndef BUSMANAGER_H
#define BUSMANAGER_H

#include "RoutingEngine.h"
#include <iostream>

class BusManager {
private:
    RoutingEngine& engine;
    unsigned int graphSize;

public:
    BusManager(RoutingEngine& engine, unsigned int graphSize);

    void addBus(unsigned int A, unsigned int B);

    void printDetails(unsigned int busNumber, unsigned int A, unsigned int B);
};

#endif // BUSMANAGER_H

