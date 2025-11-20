cmake_minimum_required(VERSION 3.10)
project(Ascend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(ascend
    src/main.cpp
    src/building.cpp
    src/elevator.cpp
    src/request.cpp
    src/ElevatorFSM.cpp
    src/terminal_ui.cpp
    src/config.cpp
    src/web_server.cpp
)

# Include the src directory for headers
target_include_directories(ascend PUBLIC 
    src
    libs/json/include
    libs/httplib
)

# Find and link ncurses
find_package(Curses REQUIRED)
target_link_libraries(ascend PRIVATE ${CURSES_LIBRARIES})

# Add the FSM generator executable
add_executable(fsm_generator fsm_generator/main.cpp)
