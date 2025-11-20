# Ascend – Elevator Optimization & FSM Simulation

Ascend is a simulation project about how elevators decide where to go next in multi-floor buildings.  
It models real elevator logic, the way they respond to up/down calls, manage multiple requests, and pick the best next stop, using C/C++ and finite state machines (FSMs).

The goal is to explore how real-time, event-driven systems work, and how FSMs can make that logic more modular and maintainable. It’s also a way to practice code generation and structured system design in C++.

---

## Project Overview

Modern elevators don’t just go to the nearest floor. They make decisions based on direction, waiting time, and system load.  
Ascend aims to capture that decision-making process in a simplified but realistic way.

The project teaches or demonstrates:

- How to build event-driven simulations  
- How to design and implement FSM-based logic  
- How to auto-generate FSM code from simple definitions  
- How to balance optimization and simplicity in algorithms  

---

## What’s an FSM?

A **Finite State Machine (FSM)** describes a system that can be in one of several **states**, changing from one to another when certain **events** happen.

In other words:
```
Idle → MovingUp → DoorOpen → Idle
```


Ascend doesn’t just use FSMs, it generates them.  
It can read external `.fsm` files and turn them into C++ code, so the elevator’s behavior can be redefined without editing the main program.  
That makes it part simulator, part code generator.

---

## Roadmap

**Phase 1 — Basic Simulation**  
- [x] Floors, elevators, and event sequence  
- [x] Simple optimization (nearest elevator selection)

**Phase 2 — FSM Integration**  
- [x] Define elevator behavior through FSM files  
- [x] Add FSM Generator module (`.fsm` → `.h/.cpp`)  
- [x] Log state transitions

**Phase 3 — Advanced Features**  
- [x] Multiple elevator coordination  
- [x] Time-based (tick-driven) simulation  
- [x] Event queue and asynchronous handling  
- [x] Terminal visualization (ASCII UI or ncurses)

**Phase 4 — Extras (Experimental)**  
- [x] Adaptive/learning elevator logic  
- [x] Configurable parameters from JSON/INI  
- [x] Optional GUI or web interface  

---

## New Features in Phase 4

Phase 4 introduces significant enhancements to the Ascend simulation, focusing on configurability, intelligence, and user interaction:

*   **Configurable Parameters (JSON/INI)**: The simulation now reads its parameters (number of floors, elevators, simulation steps, etc.) from a `config.json` file. This allows for easy customization of simulation scenarios without recompiling the code.
*   **Adaptive/Learning Elevator Logic**: The elevator system incorporates basic adaptive logic. During simulated "peak hours," idle elevators are intelligently repositioned to the ground floor to anticipate and efficiently handle increased traffic.
*   **Optional GUI or Web Interface**: In addition to the terminal-based UI, a new web interface is available. This provides a graphical representation of the simulation state, accessible via a web browser, offering a more intuitive and remote monitoring experience.

For more detailed information on how to use and develop Ascend, please refer to the following documentation:
*   [Usage Guide](docs/USAGE.md)
*   [Development Guide](docs/DEVELOPMENT.md)

---

## Architecture

Here’s the current top-level structure of the system:

<p align="center">
  <img src="docs/architecture.svg" width="600" alt="Ascend Architecture Diagram"/>
</p>

---