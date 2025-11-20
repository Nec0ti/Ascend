#include "building.h"
#include "request.h"
#include "terminal_ui.h"
#include <thread>
#include <chrono>

int main() {
    const int NUM_FLOORS = 10;
    const int NUM_ELEVATORS = 3;

    Building building(NUM_FLOORS, NUM_ELEVATORS);
    TerminalUI ui(building);

    // Add some initial requests
    building.addRequest(Request(1, 8));
    building.addRequest(Request(5, 2));
    building.addRequest(Request(3, 7));
    building.addRequest(Request(9, 0));


    // Main simulation loop
    for (int i = 0; i < 100; ++i) {
        building.runSimulationStep();
        ui.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}

