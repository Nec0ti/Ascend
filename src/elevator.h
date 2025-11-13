#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>

#include <string>

#include "ElevatorFSM.h"



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

    ElevatorFSMState getState() const;

        Direction getDirection() const;

        bool isTargetFloor(int floor) const;

        const std::vector<int>& getTargetFloors() const;

    

        std::string stateToString() const;

    

    std::string directionToString() const;



private:

    int id;

    ElevatorFSM fsm;

    int currentFloor;

    std::vector<int> targetFloors;

    Direction direction;

    int numFloors;

};

#endif
