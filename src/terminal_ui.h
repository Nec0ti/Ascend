#ifndef TERMINAL_UI_H
#define TERMINAL_UI_H

#include "building.h"
#include <ncurses.h>

class TerminalUI {
public:
    TerminalUI(Building& building);
    ~TerminalUI();

    void draw();

private:
    void drawBuilding();
    void drawElevators();
    void drawRequests();

    Building& building;
    WINDOW* buildingWindow;
    WINDOW* elevatorWindow;
    WINDOW* requestWindow;
    WINDOW* statusWindow;
};

#endif
