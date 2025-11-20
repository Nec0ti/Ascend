#include "web_server.h"
#include <iostream>

WebServer::WebServer(Building& building, SimulationController& controller, int port)
    : building(building), controller(controller), port(port) {
    // Serve static files from the "web" directory
    svr.set_base_dir("./web");

    svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Allow CORS for web client
        res.set_content_type("text/html");
        res.send_file("./web/index.html");
    });

    svr.Get("/style.css", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Allow CORS for web client
        res.set_content_type("text/css");
        res.send_file("./web/style.css");
    });

    svr.Get("/script.js", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Allow CORS for web client
        res.set_content_type("application/javascript");
        res.send_file("./web/script.js");
    });

    svr.Get("/state", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Allow CORS for web client
        res.set_content(getSimulationState().dump(), "application/json");
    });

    svr.Post("/start", [&](const httplib::Request& req, httplib::Response& res) {
        controller.start();
        res.set_content("Simulation started", "text/plain");
    });

    svr.Post("/stop", [&](const httplib::Request& req, httplib::Response& res) {
        controller.stop();
        res.set_content("Simulation stopped", "text/plain");
    });

    svr.Post("/reset", [&](const httplib::Request& req, httplib::Response& res) {
        controller.reset();
        res.set_content("Simulation reset", "text/plain");
    });
}

void WebServer::run() {
    std::cout << "Web server listening on http://localhost:" << port << std::endl;
    svr.listen("0.0.0.0", port);
}

json WebServer::getSimulationState() {
    json state;
    state["time"] = building.getCurrentTime();
    state["num_floors"] = building.getNumFloors();

    json elevators_json = json::array();
    for (const auto& elevator : building.getElevators()) {
        elevators_json.push_back({
            {"id", elevator.getId()},
            {"current_floor", elevator.getCurrentFloor()},
            {"state", elevator.stateToString()},
            {"direction", elevator.directionToString()}
        });
    }
    state["elevators"] = elevators_json;

    json requests_json = json::array();
    for (const auto& request : building.getPendingRequests()) {
        requests_json.push_back({
            {"from", request.getFromFloor()},
            {"to", request.getToFloor()}
        });
    }
    state["pending_requests"] = requests_json;

    return state;
}
