#include <iostream>
#include "building.h"
#include "request.h"

int main() {
    std::cout << "Starting Ascend simulation..." << std::endl;

    const int NUM_FLOORS = 10;
    const int NUM_ELEVATORS = 2;

    Building building(NUM_FLOORS, NUM_ELEVATORS);

    // Add some initial requests
    building.addRequest(Request(1, 8));
    building.addRequest(Request(5, 2));

    // Run the simulation for a few steps
    for (int i = 0; i < 15; ++i) {
        std::cout << "\n--- Simulation Step " << i + 1 << " ---" << std::endl;
        building.runSimulationStep();
    }

    std::cout << "\nSimulation finished." << std::endl;

    return 0;
}
