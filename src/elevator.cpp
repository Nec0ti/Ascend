#include "elevator.h"
#include <iostream>
#include <algorithm>

Elevator::Elevator(int id, int numFloors)
    : id(id),
      currentFloor(0),
      direction(Direction::NONE),
      numFloors(numFloors) {}

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
                } else {
                    if (targetFloors.front() > currentFloor) {
                        direction = Direction::UP;
                        currentFloor++;
                    } else {
                        direction = Direction::DOWN;
                        currentFloor--;
                    }
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
    if (std::find(targetFloors.begin(), targetFloors.end(), floor) != targetFloors.end()) {
        return;
    }

    targetFloors.push_back(floor);
    if (fsm.getState() == ElevatorFSMState::Idle) {
        fsm.handleEvent(ElevatorFSMEvent::CallReceived);
        if (targetFloors.front() > currentFloor) {
            direction = Direction::UP;
        } else if (targetFloors.front() < currentFloor) {
            direction = Direction::DOWN;
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
