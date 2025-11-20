#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "httplib.h"
#include "building.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class WebServer {
public:
    WebServer(Building& building, int port = 8080);
    void run();

private:
    Building& building;
    httplib::Server svr;
    int port;

    json getSimulationState();
};

#endif
