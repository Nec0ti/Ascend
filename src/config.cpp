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

int Config::getRequestGenerationIntervalMin() const {
    return data["simulation"]["request_generation_interval_min"];
}

int Config::getRequestGenerationIntervalMax() const {
    return data["simulation"]["request_generation_interval_max"];
}

std::vector<int> Config::getPeakHoursStart() const {
    return data["simulation"]["peak_hours_start"].get<std::vector<int>>();
}

std::vector<int> Config::getPeakHoursEnd() const {
    return data["simulation"]["peak_hours_end"].get<std::vector<int>>();
}

int Config::getPeakRequestMultiplier() const {
    return data["simulation"]["peak_request_multiplier"];
}

std::vector<Request> Config::getRequests() const {
    std::vector<Request> requests;
    for (const auto& req : data["requests"]) {
        requests.emplace_back(req["from"], req["to"]);
    }
    return requests;
}
