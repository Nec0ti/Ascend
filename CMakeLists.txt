cmake_minimum_required(VERSION 3.10)
project(Ascend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options for building UIs
option(BUILD_TERMINAL_UI "Build with ncurses terminal UI" ON)
option(BUILD_WEB_UI "Build with web UI" ON)

# Source files common to all builds
set(ASCEND_SOURCES
    src/main.cpp
    src/building.cpp
    src/elevator.cpp
    src/request.cpp
    src/ElevatorFSM.cpp
    src/config.cpp
    src/simulation_controller.cpp
)

# Include directories common to all builds
set(ASCEND_INCLUDE_DIRS
    src
    libs/json/include
)

# Libraries common to all builds
set(ASCEND_LIBRARIES)

# Conditional compilation for Terminal UI
if(BUILD_TERMINAL_UI)
    list(APPEND ASCEND_SOURCES src/terminal_ui.cpp)
    find_package(Curses REQUIRED)
    list(APPEND ASCEND_LIBRARIES ${CURSES_LIBRARIES})
endif()

# Conditional compilation for Web UI
if(BUILD_WEB_UI)
    list(APPEND ASCEND_SOURCES src/web_server.cpp)
    list(APPEND ASCEND_INCLUDE_DIRS libs/httplib)
    # httplib is header-only, so no extra library linking needed unless using SSL
endif()

# Add the executable
add_executable(ascend ${ASCEND_SOURCES})

# Include directories
target_include_directories(ascend PUBLIC ${ASCEND_INCLUDE_DIRS})

# Link libraries
target_link_libraries(ascend PRIVATE ${ASCEND_LIBRARIES})

# Add the FSM generator executable
add_executable(fsm_generator fsm_generator/main.cpp)
