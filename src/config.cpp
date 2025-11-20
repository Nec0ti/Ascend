#include "config.h"
#include <fstream>

Config::Config(const std::string& filename) {
    std::ifstream f(filename);
    data = json::parse(f);
}

int Config::getNumFloors() const {
    return data["simulation"]["num_floors"];
}

int Config::getNumElevators() const {
    return data["simulation"]["num_elevators"];
}

int Config::getSimulationSteps() const {
    return data["simulation"]["simulation_steps"];
}

int Config::getStepDelayMs() const {
    return data["simulation"]["step_delay_ms"];
}

std::vector<Request> Config::getRequests() const {
    std::vector<Request> requests;
    for (const auto& req : data["requests"]) {
        requests.emplace_back(req["from"], req["to"]);
    }
    return requests;
}
