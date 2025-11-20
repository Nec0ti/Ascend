#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "httplib.h"
#include "building.h"
#include "nlohmann/json.hpp"
#include "simulation_controller.h" // Include SimulationController header

using json = nlohmann::json;

class WebServer {
public:
    WebServer(Building& building, SimulationController& controller, int port = 8080); // Modified constructor
    void run();

private:
    Building& building;
    SimulationController& controller; // Reference to the SimulationController
    httplib::Server svr;
    int port;

    json getSimulationState();
};

#endif
