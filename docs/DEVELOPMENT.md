# Development Guide for Ascend Elevator Simulation

This guide provides information for developers who want to understand, compile, modify, or extend the Ascend elevator simulation project.

## Project Structure

The project is organized as follows:

*   **`CMakeLists.txt`**: The main CMake build script for the project.
*   **`src/`**: Contains the core C++ source code for the simulation.
    *   **`main.cpp`**: The entry point of the application, initializes the simulation, UI, and web server.
    *   **`building.h` / `building.cpp`**: Defines the `Building` class, which manages floors, elevators, and requests.
    *   **`elevator.h` / `elevator.cpp`**: Defines the `Elevator` class, including its state machine logic and movement.
    *   **`request.h` / `request.cpp`**: Defines the `Request` class for elevator calls.
    *   **`ElevatorFSM.h` / `ElevatorFSM.cpp`**: Implements the Finite State Machine for individual elevators.
    *   **`terminal_ui.h` / `terminal_ui.cpp`**: Handles the ncurses-based terminal user interface.
    *   **`config.h` / `config.cpp`**: Manages loading and accessing simulation parameters from `config.json`.
    *   **`web_server.h` / `web_server.cpp`**: Implements the HTTP server and REST API for the web interface.
*   **`fsm/`**: Contains the `.fsm` definition files used by the FSM generator.
*   **`fsm_generator/`**: Contains the C++ source code for the FSM code generator.
*   **`libs/`**: Contains external single-header C++ libraries added as Git submodules.
    *   **`json/`**: `nlohmann/json` library for JSON parsing.
    *   **`httplib/`**: `yhirose/cpp-httplib` library for the HTTP server.
*   **`docs/`**: Contains project documentation, including this guide.
*   **`config.json`**: Configuration file for simulation parameters.

## Compilation

The project uses CMake for its build system.

### Prerequisites

Ensure you have the following installed on your system:

*   **CMake** (version 3.10 or higher)
*   **C++ Compiler** (e.g., GCC/G++ 7 or higher)
*   **ncurses development libraries** (e.g., `libncurses-dev` on Debian/Ubuntu, `ncurses-devel` on Fedora)

### Build Steps

1.  **Clone the repository and initialize submodules:**
    ```bash
    git clone --recurse-submodules https://github.com/Nec0ti/Ascend.git
    cd Ascend
    ```
    If you cloned without `--recurse-submodules`, you can initialize them later:
    ```bash
    git submodule update --init --recursive
    ```

2.  **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```

4.  **Build the project:**
    ```bash
    make
    ```

This will compile the `ascend` executable (the main simulation) and `fsm_generator` (the FSM code generation tool) in the `build/` directory.

## Modifying and Extending the Project

### Adding New FSM States or Events

The elevator's behavior is defined by a Finite State Machine.

1.  **Modify `fsm/elevator.fsm`**: Edit this file to add new states, events, or transitions.
2.  **Run `fsm_generator`**:
    ```bash
    ./build/fsm_generator
    ```
    This will regenerate `src/ElevatorFSM.h` and `src/ElevatorFSM.cpp` based on your `.fsm` definition.
3.  **Update `elevator.cpp`**: Adjust the `Elevator::update()` method to handle any new states or events as needed.

### Enhancing Elevator Logic

*   **`building.cpp` (`assignElevator` function)**: This is where the logic for assigning requests to elevators resides. You can modify the scoring mechanism or add more complex decision-making algorithms here to improve elevator coordination.
*   **`elevator.cpp` (`addTarget` function)**: This function determines how new target floors are added and ordered for an individual elevator. You can implement more sophisticated sorting or optimization strategies.
*   **`building.cpp` (`runSimulationStep` - adaptive logic section)**: The adaptive logic for repositioning idle elevators during peak hours is located here. You can refine the peak hour detection, add more complex learning algorithms, or implement different repositioning strategies.

### Extending the Web Interface

The web interface is served by `src/web_server.cpp` and uses a simple HTML/JavaScript client embedded directly in the C++ code.

*   **`src/web_server.cpp`**:
    *   Modify the `WebServer::getSimulationState()` method to expose more simulation data via the `/state` REST API endpoint.
    *   Edit the embedded HTML/JavaScript string to change the appearance or functionality of the web UI. You can add more complex visualizations or interactive elements.
*   **External Assets**: For more complex web interfaces, consider serving static HTML, CSS, and JavaScript files from a dedicated `web/` directory. You would need to modify `web_server.cpp` to serve these files.

### Adding New Configuration Parameters

1.  **Modify `config.json`**: Add new key-value pairs to define your new parameters.
2.  **Update `src/config.h`**: Add corresponding getter methods to the `Config` class.
3.  **Update `src/config.cpp`**: Implement the new getter methods to extract values from the `json` data.
4.  **Integrate**: Use the new configuration parameters in the relevant parts of your C++ code (e.g., `main.cpp`, `building.cpp`).

## Contributing

Feel free to fork the repository, make your changes, and submit pull requests. Please ensure your code adheres to the existing style and passes compilation.
