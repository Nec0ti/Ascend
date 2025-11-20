#include "terminal_ui.h"
#include <ncurses.h>

TerminalUI::TerminalUI(Building& building) : building(building) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();

    // Initialize color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Default
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Elevator moving
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Elevator idle
    init_pair(4, COLOR_RED, COLOR_BLACK);   // Request pending

    int height, width;
    getmaxyx(stdscr, height, width);

    // Define window dimensions and positions
    int building_h = height;
    int building_w = width / 3;
    int building_y = 0;
    int building_x = 0;

    int elevator_h = height / 2;
    int elevator_w = width - building_w;
    int elevator_y = 0;
    int elevator_x = building_w;

    int request_h = height / 2;
    int request_w = width - building_w;
    int request_y = height / 2;
    int request_x = building_w;

    // Create windows
    buildingWindow = newwin(building_h, building_w, building_y, building_x);
    elevatorWindow = newwin(elevator_h, elevator_w, elevator_y, elevator_x);
    requestWindow = newwin(request_h, request_w, request_y, request_x);
    statusWindow = newwin(3, width, height - 3, 0); // Small status bar at the bottom
}

TerminalUI::~TerminalUI() {
    delwin(buildingWindow);
    delwin(elevatorWindow);
    delwin(requestWindow);
    delwin(statusWindow);
    endwin();
}

void TerminalUI::draw() {
    werase(stdscr);
    werase(buildingWindow);
    werase(elevatorWindow);
    werase(requestWindow);
    werase(statusWindow);

    drawBuilding();
    drawElevators();
    drawRequests();
    drawStatus();

    wrefresh(stdscr);
    wrefresh(buildingWindow);
    wrefresh(elevatorWindow);
    wrefresh(requestWindow);
    wrefresh(statusWindow);
}

void TerminalUI::drawBuilding() {
    box(buildingWindow, 0, 0);
    mvwprintw(buildingWindow, 0, 2, "Building");

    int numFloors = building.getNumFloors();
    for (int i = 0; i < numFloors; ++i) {
        mvwprintw(buildingWindow, numFloors - i, 2, "Floor %d", i);
    }
}

void TerminalUI::drawElevators() {
    box(elevatorWindow, 0, 0);
    mvwprintw(elevatorWindow, 0, 2, "Elevators");

    const auto& elevators = building.getElevators();
    int y = 2;
    for (const auto& elevator : elevators) {
        std::string doorStatus = (elevator.getState() == ElevatorFSMState::DoorOpen) ? "[-]" : "[ ]";
        mvwprintw(elevatorWindow, y++, 2, "Elevator %d: Floor %d, State: %s, Dir: %s %s (Dist: %d, Served: %d)",
                  elevator.getId(), elevator.getCurrentFloor(),
                  elevator.stateToString().c_str(), elevator.directionToString().c_str(),
                  doorStatus.c_str(), elevator.getTotalDistance(), elevator.getPassengersServed());
    }
}

void TerminalUI::drawRequests() {
    box(requestWindow, 0, 0);
    mvwprintw(requestWindow, 0, 2, "Requests");

    const auto& requests = building.getPendingRequests();
    int y = 2;
    for (const auto& request : requests) {
        mvwprintw(requestWindow, y++, 2, "Request: From %d to %d",
                  request.getFromFloor(), request.getToFloor());
    }
}

void TerminalUI::drawStatus() {
    box(statusWindow, 0, 0);
    mvwprintw(statusWindow, 1, 2, "Simulation Time: %d", building.getCurrentTime());
}
