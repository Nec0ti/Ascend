#include <iostream>
#include <iomanip> // For std::setw
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
    building.addRequest(Request(3, 7)); // Added a new request to test

    // Run the simulation for a few steps
    for (int i = 0; i < 20; ++i) { // Increased steps for more observation
        std::cout << "\n--- Simulation Step " << i + 1 << " ---" << std::endl;
        building.runSimulationStep();

        // Display elevator status in a table
        std::cout << std::setw(10) << "Elevator"
                  << std::setw(15) << "Current Floor"
                  << std::setw(15) << "State"
                  << std::setw(15) << "Direction" << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
        for (const auto& elevator : building.getElevators()) {
            std::cout << std::setw(10) << elevator.getId()
                      << std::setw(15) << elevator.getCurrentFloor()
                      << std::setw(15) << elevator.stateToString()
                      << std::setw(15) << elevator.directionToString() << std::endl;
        }
    }

    std::cout << "\nSimulation finished." << std::endl;

    return 0;
}
