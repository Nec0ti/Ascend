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
)

# Include the src directory for headers
target_include_directories(ascend PUBLIC src)
