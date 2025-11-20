#include "web_server.h"
#include <iostream>

WebServer::WebServer(Building& building, int port) : building(building), port(port) {
    svr.Get("/state", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Allow CORS for web client
        res.set_content(getSimulationState().dump(), "application/json");
    });

    svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_content("<!DOCTYPE html>\n"
                        "<html>\n"
                        "<head>\n"
                        "    <title>Elevator Simulation</title>\n"
                        "    <style>\n"
                        "        body { font-family: monospace; }\n"
                        "        .floor { border: 1px solid black; padding: 5px; margin: 2px; }\n"
                        "        .elevator { background-color: gray; color: white; padding: 3px; margin: 1px; display: inline-block; }\n"
                        "    </style>\n"
                        "</head>\n"
                        "<body>\n"
                        "    <h1>Elevator Simulation</h1>\n"
                        "    <div id=\"simulation-state\">Loading...</div>\n"
                        "\n"
                        "    <script>\n"
                        "        async function fetchState() {\n"
                        "            const response = await fetch('/state');\n"
                        "            const state = await response.json();\n"
                        "            \n"
                        "            let html = `<h2>Time: ${state.time}</h2>`;\n"
                        "            html += `<h3>Floors: ${state.num_floors}</h3>`;\n"
                        "            html += `<h3>Elevators:</h3>`;\n"
                        "            state.elevators.forEach(e => {\n"
                        "                html += `<div class=\"elevator\">Elevator ${e.id}: Floor ${e.current_floor}, State: ${e.state}, Dir: ${e.direction}</div>`;\n"
                        "            });\n"
                        "            html += `<h3>Pending Requests:</h3>`;\n"
                        "            state.pending_requests.forEach(r => {\n"
                        "                html += `<div>From ${r.from} to ${r.to}</div>`;\n"
                        "            });\n"
                        "\n"
                        "            document.getElementById('simulation-state').innerHTML = html;\n"
                        "        }\n"
                        "\n"
                        "        setInterval(fetchState, 500);\n"
                        "        fetchState();\n"
                        "    </script>\n"
                        "</body>\n"
                        "</html>", "text/html");
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
