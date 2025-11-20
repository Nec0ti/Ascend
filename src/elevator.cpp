#include "elevator.h"
#include <iostream>
#include <algorithm>

Elevator::Elevator(int id, int numFloors)
    : id(id),
      currentFloor(0),
      direction(Direction::NONE),
      numFloors(numFloors),
      totalDistance(0),        // Initialize statistics
      passengersServed(0) {}    // Initialize statistics

void Elevator::update() {
    switch (fsm.getState()) {
        case ElevatorFSMState::Idle:
            // Do nothing
            break;
        case ElevatorFSMState::Moving:
            if (targetFloors.empty()) {
                fsm.handleEvent(ElevatorFSMEvent::AllTargetsReached);
                direction = Direction::NONE;
            } else {
                int targetFloor = targetFloors.front();
                if (currentFloor == targetFloor) {
                    fsm.handleEvent(ElevatorFSMEvent::FloorReached);
                    targetFloors.erase(targetFloors.begin());
                    passengersServed++; // Increment passengers served when a floor is reached
                } else {
                    int prevFloor = currentFloor;
                    if (targetFloors.front() > currentFloor) {
                        direction = Direction::UP;
                        currentFloor++;
                    } else {
                        direction = Direction::DOWN;
                        currentFloor--;
                    }
                    totalDistance += std::abs(currentFloor - prevFloor); // Update total distance
                }
            }
            break;
        case ElevatorFSMState::DoorOpen:
            // In a real scenario, this would be a timed event
            fsm.handleEvent(ElevatorFSMEvent::DoorClosed);
            break;
    }
}

void Elevator::addTarget(int floor) {
    // Avoid adding duplicate targets
    if (std::find(targetFloors.begin(), targetFloors.end(), floor) != targetFloors.end()) {
        return;
    }

    targetFloors.push_back(floor);

    // If idle, determine direction and sort
    if (fsm.getState() == ElevatorFSMState::Idle) {
        fsm.handleEvent(ElevatorFSMEvent::CallReceived);
        if (!targetFloors.empty()) {
            if (targetFloors.front() > currentFloor) {
                direction = Direction::UP;
                std::sort(targetFloors.begin(), targetFloors.end());
            } else if (targetFloors.front() < currentFloor) {
                direction = Direction::DOWN;
                std::sort(targetFloors.begin(), targetFloors.end(), std::greater<int>());
            }
        }
    } else {
        // If moving, try to insert in a way that picks up on the way
        if (direction == Direction::UP) {
            std::sort(targetFloors.begin(), targetFloors.end());
        } else if (direction == Direction::DOWN) {
            std::sort(targetFloors.begin(), targetFloors.end(), std::greater<int>());
        }
    }
}

bool Elevator::isTargetFloor(int floor) const {
    return std::find(targetFloors.begin(), targetFloors.end(), floor) != targetFloors.end();
}

const std::vector<int>& Elevator::getTargetFloors() const {
    return targetFloors;
}

int Elevator::getId() const {
    return id;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

ElevatorFSMState Elevator::getState() const {
    return fsm.getState();
}

Direction Elevator::getDirection() const {
    return direction;
}

std::string Elevator::stateToString() const {
    return fsm.stateToString();
}

std::string Elevator::directionToString() const {
    switch (direction) {
        case Direction::UP: return "UP";
        case Direction::DOWN: return "DOWN";
        case Direction::NONE: return "NONE";
    }
    return "UNKNOWN";
}

int Elevator::getTotalDistance() const {
    return totalDistance;
}

int Elevator::getPassengersServed() const {
    return passengersServed;
}
