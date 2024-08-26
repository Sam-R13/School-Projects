/*
 * The purpose of this header file and its corresponding source file is to trace
 * and print the command and parent process of each child process recursively
 * back to the ultimate parent process, ppid = 0.
 * Copyright 2020 rabesj@miamioh.edu
 */
#include <unordered_map>
#include <iostream>
#include <string>


using pidPpidMap = std::unordered_map<int, int>;
using pidCmdMap = std::unordered_map<int, std::string>;

#ifndef RABESJ_HW3_H
#define RABESJ_HW3_H
class stackTrace {
private:
    pidPpidMap processes;
    pidCmdMap commands;
    
public:
    /**
     * Build maps should fill the processes map and the commands map with keys
     * and values from input passed by the user
     * @param is this is a generic input stream for better compatibility, but
     * ideally the user would pass a file stream connected to a text file
     */
    void buildMaps(std::istream& is);
    /**
     * This method uses the existing maps to print out a trace of processes
     * back to the original root process
     * @param pid the pid of the starting process
     * @param os this is a generic output stream that we are writing the trace
     * to. Usually this will just be cout, but it could be written to a file if
     * needed
     */
    void printTrace(int pid, std::ostream& os);
    /**
     * This helper method will check if a pid is found in the maps.
     * @param pid the process ID we are searching for
     * @return true if found, false otherwise
     */
    bool findPid(int pid) const;
};
#endif /* RABESJ_HW3_H */
