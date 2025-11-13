#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

struct Transition {
    std::string event;
    std::string nextState;
    std::string action;
};

struct State {
    std::string name;
    std::vector<Transition> transitions;
};

struct FSM {
    std::string name;
    std::vector<State> states;
};

class Parser {
public:
    FSM parse(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open FSM file: " << filePath << std::endl;
            exit(1);
        }

        FSM fsm;
        std::string line;
        State* currentState = nullptr;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string keyword;
            ss >> keyword;

            if (keyword == "FSM") {
                ss >> fsm.name;
            } else if (keyword == "STATE") {
                State newState;
                ss >> newState.name;
                fsm.states.push_back(newState);
                currentState = &fsm.states.back();
            } else if (keyword == "ON") {
                if (currentState) {
                    Transition newTransition;
                    ss >> newTransition.event;
                    std::string gotoKeyword;
                    ss >> gotoKeyword; // "GOTO"
                    ss >> newTransition.nextState;
                    std::string doKeyword;
                    ss >> doKeyword; // "DO"
                    if (doKeyword == "DO") {
                        ss >> newTransition.action;
                    }
                    currentState->transitions.push_back(newTransition);
                }
            }
        }

        return fsm;
    }
};

class CodeGenerator {
public:
    void generate(const FSM& fsm, const std::string& outputDir) {
        generateHeader(fsm, outputDir);
        generateSource(fsm, outputDir);
    }

private:
    void generateHeader(const FSM& fsm, const std::string& outputDir) {
        std::string filePath = outputDir + "/" + fsm.name + ".h";
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open header file for writing: " << filePath << std::endl;
            return;
        }

        file << "#ifndef " << fsm.name << "_H" << std::endl;
        file << "#define " << fsm.name << "_H" << std::endl;
        file << std::endl;
        file << "#include <string>" << std::endl;
        file << std::endl;

        // State enum
        file << "enum class " << fsm.name << "State {" << std::endl;
        for (const auto& state : fsm.states) {
            file << "    " << state.name << "," << std::endl;
        }
        file << "};" << std::endl;
        file << std::endl;

        // Event enum
        std::set<std::string> events;
        for (const auto& state : fsm.states) {
            for (const auto& transition : state.transitions) {
                events.insert(transition.event);
            }
        }
        file << "enum class " << fsm.name << "Event {" << std::endl;
        for (const auto& event : events) {
            file << "    " << event << "," << std::endl;
        }
        file << "};" << std::endl;
        file << std::endl;

        // FSM class
        file << "class " << fsm.name << " {" << std::endl;
        file << "public:" << std::endl;
        file << "    " << fsm.name << "();" << std::endl;
        file << "    void handleEvent(" << fsm.name << "Event event);" << std::endl;
        file << "    " << fsm.name << "State getState() const;" << std::endl;
        file << "    std::string stateToString() const;" << std::endl;
        file << std::endl;
        file << "private:" << std::endl;
        file << "    " << fsm.name << "State currentState;" << std::endl;
        file << "    std::string stateToString(" << fsm.name << "State state) const;" << std::endl;
        file << "};" << std::endl;
        file << std::endl;

        file << "#endif // " << fsm.name << "_H" << std::endl;
    }

    void generateSource(const FSM& fsm, const std::string& outputDir) {
        std::string filePath = outputDir + "/" + fsm.name + ".cpp";
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open source file for writing: " << filePath << std::endl;
            return;
        }

        file << "#include \"" << fsm.name << ".h\"" << std::endl;
        file << "#include <iostream>" << std::endl;
        file << std::endl;

        // Constructor
        file << fsm.name << "::" << fsm.name << "() : currentState(" << fsm.name << "State::" << fsm.states[0].name << ") {}" << std::endl;
        file << std::endl;

        // handleEvent
        file << "void " << fsm.name << "::handleEvent(" << fsm.name << "Event event) {" << std::endl;
        file << "    " << fsm.name << "State nextState = currentState;" << std::endl;
        file << "    switch (currentState) {" << std::endl;
        for (const auto& state : fsm.states) {
            file << "        case " << fsm.name << "State::" << state.name << ":" << std::endl;
            file << "            switch (event) {" << std::endl;
            for (const auto& transition : state.transitions) {
                file << "                case " << fsm.name << "Event::" << transition.event << ":" << std::endl;
                file << "                    nextState = " << fsm.name << "State::" << transition.nextState << ";" << std::endl;
                // TODO: Call action
                file << "                    break;" << std::endl;
            }
            file << "                default:" << std::endl;
            file << "                    break;" << std::endl;
            file << "            }" << std::endl;
            file << "            break;" << std::endl;
        }
        file << "    }" << std::endl;
        file << "    if (nextState != currentState) {" << std::endl;
        file << "        std::cout << \"FSM: " << fsm.name << " state changed from \" << stateToString() << \" to \" << stateToString(nextState) << std::endl;" << std::endl;
        file << "        currentState = nextState;" << std::endl;
        file << "    }" << std::endl;
        file << "}" << std::endl;
        file << std::endl;

        // getState
        file << fsm.name << "State " << fsm.name << "::getState() const {" << std::endl;
        file << "    return currentState;" << std::endl;
        file << "}" << std::endl;
        file << std::endl;

        // stateToString
        file << "std::string " << fsm.name << "::stateToString() const {" << std::endl;
        file << "    return stateToString(currentState);" << std::endl;
        file << "}" << std::endl;
        file << std::endl;

        // stateToString helper
        file << "std::string " << fsm.name << "::stateToString(" << fsm.name << "State state) const {" << std::endl;
        file << "    switch (state) {" << std::endl;
        for (const auto& state : fsm.states) {
            file << "        case " << fsm.name << "State::" << state.name << ": return \"" << state.name << "\";" << std::endl;
        }
        file << "    }" << std::endl;
        file << "    return \"UNKNOWN\";" << std::endl;
        file << "}" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <fsm_file> <output_dir>" << std::endl;
        return 1;
    }

    std::string fsmFilePath = argv[1];
    std::string outputDir = argv[2];
    std::cout << "Generating FSM code from: " << fsmFilePath << " to " << outputDir << std::endl;

    Parser parser;
    FSM fsm = parser.parse(fsmFilePath);

    CodeGenerator generator;
    generator.generate(fsm, outputDir);

    std::cout << "FSM code generation complete." << std::endl;

    return 0;
}
