#include "elevator.h"
#include <iostream>
#include <algorithm>

Elevator::Elevator(int id, int numFloors)
    : id(id),
      state(ElevatorState::IDLE),
      currentFloor(0),
      direction(Direction::NONE),
      numFloors(numFloors) {}

void Elevator::update() {
    if (state == ElevatorState::IDLE) {
        return;
    }

    if (!targetFloors.empty()) {
        int targetFloor = targetFloors.front();
        if (currentFloor == targetFloor) {
            std::cout << "Elevator " << id << " reached target floor " << targetFloor << std::endl;
            targetFloors.erase(targetFloors.begin());

            if (targetFloors.empty()) {
                state = ElevatorState::IDLE;
                direction = Direction::NONE;
                std::cout << "Elevator " << id << " is now IDLE" << std::endl;
            } else {
                // Set direction to next target
                if (targetFloors.front() > currentFloor) {
                    direction = Direction::UP;
                    state = ElevatorState::MOVING_UP;
                } else if (targetFloors.front() < currentFloor) {
                    direction = Direction::DOWN;
                    state = ElevatorState::MOVING_DOWN;
                } else {
                    // Target is the current floor, handle in next update
                }
            }
        } else if (state == ElevatorState::MOVING_UP) {
            currentFloor++;
        } else if (state == ElevatorState::MOVING_DOWN) {
            currentFloor--;
        }
        std::cout << "Elevator " << id << " at floor " << currentFloor << " (State: " << static_cast<int>(state) << ")" << std::endl;
    }
}

void Elevator::addTarget(int floor) {
    targetFloors.push_back(floor);

    if (state == ElevatorState::IDLE) {
        if (targetFloors.front() > currentFloor) {
            state = ElevatorState::MOVING_UP;
            direction = Direction::UP;
            std::cout << "Elevator " << id << " state changed to MOVING_UP" << std::endl;
        } else if (targetFloors.front() < currentFloor) {
            state = ElevatorState::MOVING_DOWN;
            direction = Direction::DOWN;
            std::cout << "Elevator " << id << " state changed to MOVING_DOWN" << std::endl;
        }
    }
}

int Elevator::getId() const {
    return id;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

ElevatorState Elevator::getState() const {
    return state;
}

Direction Elevator::getDirection() const {
    return direction;
}

std::string Elevator::stateToString() const {
    switch (state) {
        case ElevatorState::IDLE: return "IDLE";
        case ElevatorState::MOVING_UP: return "MOVING_UP";
        case ElevatorState::MOVING_DOWN: return "MOVING_DOWN";
        case ElevatorState::DOOR_OPEN: return "DOOR_OPEN";
    }
    return "UNKNOWN";
}

std::string Elevator::directionToString() const {
    switch (direction) {
        case Direction::UP: return "UP";
        case Direction::DOWN: return "DOWN";
        case Direction::NONE: return "NONE";
    }
    return "UNKNOWN";
}
