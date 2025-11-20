#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#include <atomic>
#include <mutex>
#include <condition_variable>

class SimulationController {
public:
    enum class State {
        Stopped,
        Running,
        Resetting
    };

    SimulationController();

    void start();
    void stop();
    void reset();
    State getState() const;

    // For main loop to wait/notify
    void waitForRun();
    void notifyRun();

private:
    std::atomic<State> currentState;
    std::mutex mutex;
    std::condition_variable cv;
};

#endif
