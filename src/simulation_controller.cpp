#include "simulation_controller.h"

SimulationController::SimulationController() : currentState(State::Stopped) {}

void SimulationController::start() {
    std::unique_lock<std::mutex> lock(mutex);
    if (currentState == State::Stopped) {
        currentState = State::Running;
        cv.notify_all(); // Notify any waiting threads (e.g., main simulation loop)
    }
}

void SimulationController::stop() {
    std::unique_lock<std::mutex> lock(mutex);
    if (currentState == State::Running) {
        currentState = State::Stopped;
    }
}

void SimulationController::reset() {
    std::unique_lock<std::mutex> lock(mutex);
    currentState = State::Resetting;
    cv.notify_all(); // Notify main loop to reset
}

SimulationController::State SimulationController::getState() const {
    return currentState.load();
}

void SimulationController::waitForRun() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&]{ return currentState == State::Running || currentState == State::Resetting; });
}

void SimulationController::notifyRun() {
    cv.notify_all();
}
