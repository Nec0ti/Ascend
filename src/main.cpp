#include "building.h"
#include "request.h"
#include "terminal_ui.h"
#include "config.h"
#include "web_server.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    try {
        Config config("config.json");

        Building building(config.getNumFloors(), config.getNumElevators());
        TerminalUI ui(building);
        WebServer webServer(building);

        std::thread webServerThread([&]() {
            webServer.run();
        });

        for (const auto& req : config.getRequests()) {
            building.addRequest(req);
        }

        // Main simulation loop
        for (int i = 0; i < config.getSimulationSteps(); ++i) {
            building.runSimulationStep();
            ui.draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(config.getStepDelayMs()));
        }

        webServerThread.join(); // Wait for the web server thread to finish (though in this case it runs indefinitely)

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

