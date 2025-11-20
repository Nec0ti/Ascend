#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "elevator.h"
#include "request.h"
#include "config.h" // Include Config header
#include <string>
#include <random> // For random number generation
#include <numeric> // For std::iota

class Building {
public:
    Building(int numFloors, int numElevators, const Config& config); // Modified constructor

    void addRequest(const Request& request);
    void runSimulationStep();
    const std::vector<Elevator>& getElevators() const;
    int getNumFloors() const;
    const std::vector<Request>& getPendingRequests() const;
    int getCurrentTime() const;

private:
    bool assignElevator(const Request& request);
    void generateRandomRequest(); // New method

    int numFloors;
    std::vector<Elevator> elevators;
    std::vector<Request> pendingRequests;
    int currentTime;
    const Config& config; // Reference to the Config object
    int nextRequestTime; // Time when the next request should be generated

    std::mt19937 rng; // Random number generator
};

#endif