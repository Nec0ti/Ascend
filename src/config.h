#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "request.h"

using json = nlohmann::json;

class Config {
public:
    Config(const std::string& filename);

    int getNumFloors() const;
    int getNumElevators() const;
    int getSimulationSteps() const;
    int getStepDelayMs() const;
    std::vector<Request> getRequests() const;

private:
    json data;
};

#endif
