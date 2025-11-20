#include "building.h"
#include "request.h"
#include "config.h"
#include "simulation_controller.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <stdexcept> // For std::runtime_error

#ifdef BUILD_TERMINAL_UI
#include "terminal_ui.h"
#endif

#ifdef BUILD_WEB_UI
#include "web_server.h"
#endif

int main() {
    try {
        Config config("config.json");
        SimulationController simController;

        Building building(config.getNumFloors(), config.getNumElevators(), config);

#ifdef BUILD_TERMINAL_UI
        TerminalUI ui(building);
#endif

#ifdef BUILD_WEB_UI
        WebServer webServer(building, simController);
        std::thread webServerThread([&]() {
            webServer.run();
        });
#endif

        for (const auto& req : config.getRequests()) {
            building.addRequest(req);
        }

        // Main simulation loop
        int currentSimStep = 0;
        while (currentSimStep < config.getSimulationSteps()) {
            simController.waitForRun(); // Wait until simulation is running

            if (simController.getState() == SimulationController::State::Resetting) {
                // Reset simulation state (re-initialize building, requests, etc.)
                building = Building(config.getNumFloors(), config.getNumElevators(), config);
                for (const auto& req : config.getRequests()) {
                    building.addRequest(req);
                }
                currentSimStep = 0;
                simController.start(); // Automatically start after reset
                continue;
            }

            building.runSimulationStep();

#ifdef BUILD_TERMINAL_UI
            ui.draw();
#endif

            std::this_thread::sleep_for(std::chrono::milliseconds(config.getStepDelayMs()));
            currentSimStep++;
        }

#ifdef BUILD_WEB_UI
        webServerThread.join(); // Wait for the web server thread to finish (though in this case it runs indefinitely)
#endif

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

