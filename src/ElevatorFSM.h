#ifndef ElevatorFSM_H
#define ElevatorFSM_H

#include <string>

enum class ElevatorFSMState {
    Idle,
    Moving,
    DoorOpen,
};

enum class ElevatorFSMEvent {
    AllTargetsReached,
    CallReceived,
    DoorClosed,
    FloorReached,
};

class ElevatorFSM {
public:
    ElevatorFSM();
    void handleEvent(ElevatorFSMEvent event);
    ElevatorFSMState getState() const;
    std::string stateToString() const;

private:
    ElevatorFSMState currentState;
    std::string stateToString(ElevatorFSMState state) const;
};

#endif // ElevatorFSM_H
