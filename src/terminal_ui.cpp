#include "terminal_ui.h"
#include <ncurses.h>

TerminalUI::TerminalUI(Building& building) : building(building) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();

    // Initialize color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

    int height, width;
    getmaxyx(stdscr, height, width);

    buildingWindow = newwin(height, width / 2, 0, 0);
    elevatorWindow = newwin(height / 2, width / 2, 0, width / 2);
    requestWindow = newwin(height / 2, width / 2, height / 2, width / 2);
}

TerminalUI::~TerminalUI() {
    delwin(buildingWindow);
    delwin(elevatorWindow);
    delwin(requestWindow);
    endwin();
}

void TerminalUI::draw() {
    werase(stdscr);
    werase(buildingWindow);
    werase(elevatorWindow);
    werase(requestWindow);

    drawBuilding();
    drawElevators();
    drawRequests();

    wrefresh(stdscr);
    wrefresh(buildingWindow);
    wrefresh(elevatorWindow);
    wrefresh(requestWindow);
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
        mvwprintw(elevatorWindow, y++, 2, "Elevator %d: Floor %d, State: %s, Dir: %s",
                  elevator.getId(), elevator.getCurrentFloor(),
                  elevator.stateToString().c_str(), elevator.directionToString().c_str());
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
