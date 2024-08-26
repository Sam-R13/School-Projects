/*
 * Copyright 2020 rabesj@miamioh.edu
 */
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "rabesj_hw3.h"

using vectorMatrix = std::vector<std::vector<std::string>>;
void stackTrace::buildMaps(std::istream& is) {
    int pid, ppid;
    std::string word, cmd;
    while (!is.eof()) {
        is >> word;
        is >> word;
        pid = std::stoi(word);
        is >> word;
        ppid = std::stoi(word);
        is >> word >> word >> word >> word;
        std::getline(is, cmd);
        processes[pid] = ppid;
        commands[pid] = cmd;
    }
}

void stackTrace::printTrace(int pid, std::ostream& os) {
    vectorMatrix elements;
    std::vector<std::string> line;
    while (pid != 0) {
        line.push_back(std::to_string(pid));
        line.push_back(std::to_string(processes[pid]));
        line.push_back(commands[pid]);
        elements.push_back(line);
        line.clear();
        pid = processes[pid];
    }
    std::reverse(elements.begin(), elements.end());
    int i = 1;
    for (std::vector<std::string> v : elements) {
        for (std::string s : v) {
            if (i == 3) {
                os << s << std::endl;
                i = 1;
            } else {
                os << s << "\t";
                i++;
            }
        }
    }
}

bool stackTrace::findPid(int pid) const {
    return (processes.find(pid) == processes.end() ||
            commands.find(pid) == commands.end());
}

int main(int argc, char** argv) {
    // Initialize the file streams based on user input, and check to see if the
    // file was found
    std::ifstream processFile(argv[1]);
    if (!processFile.good()) {
        std::cerr << "Unable to retrieve process file\n";
        return 1;
    }
    
    // Since I know the inputs for this homework, I can safely remove the first
    // line of the input file.
    std::string line;
    std::getline(processFile, line);
    
    // Declare a stackTrace object in order to use the methods
    // Fill the maps using the input file stream
    stackTrace currentProcesses;
    currentProcesses.buildMaps(processFile);
    
    // Take the pid from the second command line argument
    // Send it to print the trace of that process
    int pid = atoi(argv[2]);
    if (pid < 1 && !currentProcesses.findPid(pid)) {
        std::cerr << "Invalid pid, program shutting down";
        return 1;
    }
    std::cout << "Process tree for PID: " << pid << "\nPID\tPPID\tCMD\n";
    currentProcesses.printTrace(pid, std::cout);
    
    return 0;
}
