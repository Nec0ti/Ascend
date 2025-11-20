#include "building.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm> // For std::shuffle

Building::Building(int numFloors, int numElevators, const Config& config)
    : numFloors(numFloors),
      currentTime(0),
      config(config),
      rng(std::random_device{}()) { // Initialize random number generator
    for (int i = 0; i < numElevators; ++i) {
        elevators.emplace_back(i, numFloors);
    }
    nextRequestTime = config.getRequestGenerationIntervalMin(); // Initial request generation time
}

void Building::addRequest(const Request& request) {
    pendingRequests.push_back(request);
}

void Building::runSimulationStep() {
    currentTime++;

    // Generate random requests
    if (currentTime >= nextRequestTime) {
        generateRandomRequest();
        int interval = std::uniform_int_distribution<>(
            config.getRequestGenerationIntervalMin(),
            config.getRequestGenerationIntervalMax())(rng);
        
        // Apply peak hour multiplier
        bool isPeakHour = false;
        for (size_t i = 0; i < config.getPeakHoursStart().size(); ++i) {
            if (currentTime >= config.getPeakHoursStart()[i] && currentTime <= config.getPeakHoursEnd()[i]) {
                isPeakHour = true;
                break;
            }
        }
        if (isPeakHour) {
            interval /= config.getPeakRequestMultiplier();
        }
        nextRequestTime = currentTime + std::max(1, interval); // Ensure interval is at least 1
    }

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

    // 3. Adaptive logic: send idle elevators to ground floor during peak hours
    bool isPeakHour = false;
    for (size_t i = 0; i < config.getPeakHoursStart().size(); ++i) {
        if (currentTime >= config.getPeakHoursStart()[i] && currentTime <= config.getPeakHoursEnd()[i]) {
            isPeakHour = true;
            break;
        }
    }

    if (isPeakHour) {
        for (auto& elevator : elevators) {
            if (elevator.getState() == ElevatorFSMState::Idle && elevator.getCurrentFloor() != 0) {
                elevator.addTarget(0);
            }
        }
    }
}

void Building::generateRandomRequest() {
    std::uniform_int_distribution<> floor_dist(0, numFloors - 1);
    int fromFloor = floor_dist(rng);
    int toFloor = floor_dist(rng);

    // Ensure fromFloor and toFloor are different
    while (toFloor == fromFloor) {
        toFloor = floor_dist(rng);
    }

    addRequest(Request(fromFloor, toFloor));
    std::cout << "Generated new request: " << fromFloor << " -> " << toFloor << " at time " << currentTime << std::endl;
}

bool Building::assignElevator(const Request& request) {
    Elevator* bestElevator = nullptr;
    int bestScore = -1; // Using -1 to indicate no suitable elevator found yet

    for (auto& elevator : elevators) {
        int score = 0;
        int distance = std::abs(elevator.getCurrentFloor() - request.getFromFloor());

        if (elevator.getState() == ElevatorFSMState::Idle) {
            // Higher score for idle elevators, with a penalty for distance
            score = 100 - distance;
        } else if (elevator.getState() == ElevatorFSMState::Moving) {
            Direction requestDirection = (request.getToFloor() > request.getFromFloor()) ? Direction::UP : Direction::DOWN;
            
            // Check if the elevator is moving towards the request's origin floor
            bool isMovingTowards = (elevator.getDirection() == Direction::UP && request.getFromFloor() > elevator.getCurrentFloor()) ||
                                   (elevator.getDirection() == Direction::DOWN && request.getFromFloor() < elevator.getCurrentFloor());

            if (isMovingTowards && elevator.getDirection() == requestDirection) {
                // Elevator is moving towards the request and in the same direction
                score = 50 - distance;
            }
        }

        if (score > bestScore) {
            bestScore = score;
            bestElevator = &elevator;
        }
    }

    if (bestElevator) {
        std::cout << "Assigning request (" << request.getFromFloor() << " -> " << request.getToFloor()
                  << ") to Elevator " << bestElevator->getId() << std::endl;
        bestElevator->addTarget(request.getFromFloor());
        bestElevator->addTarget(request.getToFloor());
        return true;
    } else {
        std::cout << "No suitable elevators available for request (" << request.getFromFloor() << " -> "
                  << request.getToFloor() << "). Request queued." << std::endl;
        return false;
    }
}

const std::vector<Elevator>& Building::getElevators() const {
    return elevators;
}

int Building::getNumFloors() const {
    return numFloors;
}

const std::vector<Request>& Building::getPendingRequests() const {
    return pendingRequests;
}

int Building::getCurrentTime() const {
    return currentTime;
}
