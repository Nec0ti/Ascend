#include "building.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

Building::Building(int numFloors, int numElevators) : numFloors(numFloors) {
    for (int i = 0; i < numElevators; ++i) {
        elevators.emplace_back(i, numFloors);
    }
}

void Building::addRequest(const Request& request) {
    pendingRequests.push_back(request);
}

void Building::runSimulationStep() {
    // 1. Assign pending requests
    std::vector<Request> unassignedRequests;
    for (const auto& req : pendingRequests) {
        if (!assignElevator(req)) {
            unassignedRequests.push_back(req);
        }
    }
    pendingRequests = unassignedRequests;

    // 2. Update all elevators
    for (auto& elevator : elevators) {
        elevator.update();
    }
}

bool Building::assignElevator(const Request& request) {
    // Simple optimization: find the nearest idle elevator.
    Elevator* bestElevator = nullptr;
    int minDistance = std::numeric_limits<int>::max();

    for (auto& elevator : elevators) {
        if (elevator.getState() == ElevatorState::IDLE) {
            int distance = std::abs(elevator.getCurrentFloor() - request.getFromFloor());
            if (distance < minDistance) {
                minDistance = distance;
                bestElevator = &elevator;
            }
        }
    }

    if (bestElevator) {
        std::cout << "Assigning request (" << request.getFromFloor() << " -> " << request.getToFloor()
                  << ") to Elevator " << bestElevator->getId() << std::endl;
        bestElevator->addTarget(request.getFromFloor());
        bestElevator->addTarget(request.getToFloor());
        return true;
    } else {
        std::cout << "No idle elevators available for request (" << request.getFromFloor() << " -> "
                  << request.getToFloor() << "). Request queued." << std::endl;
        return false;
    }
}

const std::vector<Elevator>& Building::getElevators() const {
    return elevators;
}
