#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>

enum class ElevatorState {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    DOOR_OPEN
};

enum class Direction {
    UP,
    DOWN,
    NONE
};

class Elevator {
public:
    Elevator(int id, int numFloors);

    void update();
    void addTarget(int floor);

    int getId() const;
    int getCurrentFloor() const;
    ElevatorState getState() const;
    Direction getDirection() const;

private:
    int id;
    ElevatorState state;
    int currentFloor;
    std::vector<int> targetFloors;
    Direction direction;
    int numFloors;
};

#endif
