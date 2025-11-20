# Usage Guide for Ascend Elevator Simulation

This document explains how to run the Ascend elevator simulation and how to configure its behavior using the `config.json` file.

## Running the Simulation

The Ascend simulation can be run in two modes:
1.  **Terminal UI Mode:** A text-based user interface (TUI) displayed directly in your terminal.
2.  **Web UI Mode:** A web-based interface accessible via your browser.

### Prerequisites

Before running, ensure you have compiled the project. Follow the instructions in `DEVELOPMENT.md` for compilation.

### Terminal UI Mode

To run the simulation with the terminal UI, simply execute the `ascend` executable from your build directory:

```bash
./build/ascend
```

The terminal UI will display the building layout, elevator positions, states, directions, and pending requests.

### Web UI Mode

To run the simulation with the web UI, execute the `ascend` executable. The web server will start automatically on port 8080 (default).

```bash
./build/ascend
```

Then, open your web browser and navigate to `http://localhost:8080`. The web interface will display the simulation state, refreshing automatically.

## Configuration

The simulation's behavior is controlled by the `config.json` file located in the project root directory. You can modify this file to change various parameters of the simulation.

### `config.json` Structure

```json
{
    "simulation": {
        "num_floors": 10,
        "num_elevators": 3,
        "simulation_steps": 100,
        "step_delay_ms": 200
    },
    "requests": [
        { "from": 1, "to": 8 },
        { "from": 5, "to": 2 },
        { "from": 3, "to": 7 },
        { "from": 9, "to": 0 }
    ]
}
```

### Parameters

*   **`simulation.num_floors`**: The total number of floors in the building.
*   **`simulation.num_elevators`**: The number of elevators operating in the building.
*   **`simulation.simulation_steps`**: The total number of simulation steps to run. Each step represents a unit of time in the simulation.
*   **`simulation.step_delay_ms`**: The delay in milliseconds between each simulation step. This controls the speed of the simulation.
*   **`requests`**: An array of initial elevator requests. Each request object has:
    *   **`from`**: The starting floor of the request.
    *   **`to`**: The destination floor of the request.

### Example: Changing Simulation Speed

To make the simulation run faster, you can decrease the `step_delay_ms` value:

```json
{
    "simulation": {
        "num_floors": 10,
        "num_elevators": 3,
        "simulation_steps": 200,
        "step_delay_ms": 50  // Faster simulation
    },
    "requests": [
        { "from": 1, "to": 8 }
    ]
}
```

### Example: Adding More Elevators and Requests

To simulate a larger building with more elevators and initial requests:

```json
{
    "simulation": {
        "num_floors": 15,
        "num_elevators": 5,
        "simulation_steps": 150,
        "step_delay_ms": 150
    },
    "requests": [
        { "from": 1, "to": 10 },
        { "from": 7, "to": 3 },
        { "from": 12, "to": 1 },
        { "from": 0, "to": 14 },
        { "from": 5, "to": 5 }
    ]
}
```

By modifying `config.json`, you can easily experiment with different simulation scenarios without recompiling the code.
