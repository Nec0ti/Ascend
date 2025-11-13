#include "ElevatorFSM.h"
#include <iostream>

ElevatorFSM::ElevatorFSM() : currentState(ElevatorFSMState::Idle) {}

void ElevatorFSM::handleEvent(ElevatorFSMEvent event) {
    ElevatorFSMState nextState = currentState;
    switch (currentState) {
        case ElevatorFSMState::Idle:
            switch (event) {
                case ElevatorFSMEvent::CallReceived:
                    nextState = ElevatorFSMState::Moving;
                    break;
                default:
                    break;
            }
            break;
        case ElevatorFSMState::Moving:
            switch (event) {
                case ElevatorFSMEvent::FloorReached:
                    nextState = ElevatorFSMState::DoorOpen;
                    break;
                case ElevatorFSMEvent::AllTargetsReached:
                    nextState = ElevatorFSMState::Idle;
                    break;
                default:
                    break;
            }
            break;
        case ElevatorFSMState::DoorOpen:
            switch (event) {
                case ElevatorFSMEvent::DoorClosed:
                    nextState = ElevatorFSMState::Moving;
                    break;
                default:
                    break;
            }
            break;
    }
    if (nextState != currentState) {
        std::cout << "FSM: ElevatorFSM state changed from " << stateToString() << " to " << stateToString(nextState) << std::endl;
        currentState = nextState;
    }
}

ElevatorFSMState ElevatorFSM::getState() const {
    return currentState;
}

std::string ElevatorFSM::stateToString() const {
    return stateToString(currentState);
}

std::string ElevatorFSM::stateToString(ElevatorFSMState state) const {
    switch (state) {
        case ElevatorFSMState::Idle: return "Idle";
        case ElevatorFSMState::Moving: return "Moving";
        case ElevatorFSMState::DoorOpen: return "DoorOpen";
    }
    return "UNKNOWN";
}
