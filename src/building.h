#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "elevator.h"
#include "request.h"
#include <string>

class Building {
public:
    Building(int numFloors, int numElevators);

    void addRequest(const Request& request);
    void runSimulationStep();
    const std::vector<Elevator>& getElevators() const;
    int getNumFloors() const;
    const std::vector<Request>& getPendingRequests() const;
    int getCurrentTime() const;

private:
    bool assignElevator(const Request& request);

    int numFloors;
    std::vector<Elevator> elevators;
    std::vector<Request> pendingRequests;
    int currentTime;
};

#endif