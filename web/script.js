const simulationStateElement = document.getElementById('simulation-state');
const buildingElement = document.getElementById('building');
const pendingRequestsElement = document.getElementById('pending-requests');
const elevatorStatsElement = document.getElementById('elevator-stats');
const simTimeElement = document.getElementById('sim-time');
const numFloorsElement = document.getElementById('num-floors');

const startButton = document.getElementById('start-sim');
const stopButton = document.getElementById('stop-sim');
const resetButton = document.getElementById('reset-sim');

let numFloors = 0;
let elevatorElements = {}; // To store references to elevator DOM elements
let simulationInterval;

async function fetchState() {
    try {
        const response = await fetch('/state');
        const state = await response.json();
        
        simTimeElement.textContent = state.time;

        if (state.num_floors !== numFloors) {
            numFloors = state.num_floors;
            renderBuildingStructure(numFloors);
        }

        updateElevators(state.elevators);
        updateRequests(state.pending_requests);

    } catch (error) {
        console.error('Error fetching simulation state:', error);
        // Optionally display an error message in the UI
    }
}

function renderBuildingStructure(floors) {
    buildingElement.innerHTML = ''; // Clear existing floors
    elevatorElements = {}; // Clear existing elevator elements

    for (let i = floors - 1; i >= 0; i--) {
        const floorDiv = document.createElement('div');
        floorDiv.classList.add('floor');
        floorDiv.id = `floor-${i}`;
        floorDiv.innerHTML = `<span class="floor-number">Floor ${i}</span>`;
        buildingElement.appendChild(floorDiv);
    }
    numFloorsElement.textContent = floors;
}

function updateElevators(elevators) {
    elevatorStatsElement.innerHTML = ''; // Clear previous stats

    elevators.forEach(elevator => {
        const floorDiv = document.getElementById(`floor-${elevator.current_floor}`);
        if (floorDiv) {
            let elevatorCar = elevatorElements[elevator.id];
            if (!elevatorCar) {
                // Create new elevator car if it doesn't exist
                elevatorCar = document.createElement('div');
                elevatorCar.classList.add('elevator-car');
                elevatorCar.textContent = elevator.id;
                elevatorElements[elevator.id] = elevatorCar;
                floorDiv.appendChild(elevatorCar);
            } else {
                // Move existing elevator car to the correct floor
                // Remove from old floor if it changed
                const currentParent = elevatorCar.parentNode;
                if (currentParent && currentParent.id !== `floor-${elevator.current_floor}`) {
                    currentParent.removeChild(elevatorCar);
                    floorDiv.appendChild(elevatorCar);
                }
            }

            // Update door status
            if (elevator.state === 'DoorOpen') {
                elevatorCar.classList.add('door-open');
            } else {
                elevatorCar.classList.remove('door-open');
            }
        }

        // Update elevator stats panel
        const statItem = document.createElement('div');
        statItem.classList.add('elevator-stat-item');
        statItem.innerHTML = `
            <p><strong>Elevator ${elevator.id}</strong></p>
            <p>Current Floor: ${elevator.current_floor}</p>
            <p>State: ${elevator.state}</p>
            <p>Direction: ${elevator.direction}</p>
            <p>Total Distance: ${elevator.total_distance}</p>
            <p>Passengers Served: ${elevator.passengers_served}</p>
        `;
        elevatorStatsElement.appendChild(statItem);
    });
}

function updateRequests(requests) {
    pendingRequestsElement.innerHTML = ''; // Clear previous requests
    if (requests.length === 0) {
        pendingRequestsElement.innerHTML = '<div>No pending requests.</div>';
        return;
    }
    requests.forEach(request => {
        const requestDiv = document.createElement('div');
        requestDiv.textContent = `From ${request.from} to ${request.to}`;
        pendingRequestsElement.appendChild(requestDiv);
    });
}

async function sendControlCommand(command) {
    try {
        await fetch(`/${command}`, { method: 'POST' });
    } catch (error) {
        console.error(`Error sending ${command} command:`, error);
    }
}

startButton.addEventListener('click', () => sendControlCommand('start'));
stopButton.addEventListener('click', () => sendControlCommand('stop'));
resetButton.addEventListener('click', () => sendControlCommand('reset'));

// Initial fetch and then poll every 500ms
simulationInterval = setInterval(fetchState, 500);
fetchState();
