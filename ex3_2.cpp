// Copyright (C) 2019 raodm@miamiOH.edu

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <string>

/** Simple method to read and print number of characters read 
 *
 * @param is The input stream to read data from.
 *
 * @param tag A tag to help distinguish between parent and child processes.
 *
 * @param The pid associated with the process for printing.
*/
void read(std::ifstream& is, const std::string& tag, const int& pid) {
    // Print value and address of pid to observe how the same virtual memory
    // address can contain different values in different processes because
    // the virtual memory is mapped to different parts of real memory.
    std::cout << "In " << tag << ": Pid = " << pid
                       << ", address = "    << &pid << std::endl;

    // Read data from input stream until end-of-file
    std::string line;
    long charCount = 0;  // track number of characters read so far
    while (getline(is, line)) {
        charCount += line.size() + 1;  // +1 to count newline char
    }

    // Print number of characters read. Each time the program is run
    // the parent and child will read varying number of characters
    // because: 1. context switching is non-determinisitic, 2. the
    // input stream is shared between the processes (as it was created
    // prior to fork in main).
    std::cout << tag << ": Number of characters read = "
              << (charCount - 1) << std::endl;
}

/**
 * The main method forks to run a child process. Both parent and child
 * read data from a shared input stream to demonstrate that I/O
 * streams created prior to fork are shared between parent and child.
 */
int main() {
    // Open stream before fork. That way "is" will be shared between
    // parent & child processes (after fork).    
    std::ifstream is("/usr/src/linux-source-4.15.0/"  // <-- directory
                     "linux-source-4.15.0.tar.bz2");  // <-- file in directory
    
    const int pid = fork();  // <--- Creates a child process!
    // After fork pid will be zero in child process and non-zero in parent
    if (pid == 0) {
        // In child process!
        read(is, "child", pid);
    } else {
        // In parent process!
        read(is, "parent", pid);
        std::cout << "The parent is waiting for child pid: " << pid
                  << std::endl;
        int childExitCode = -1;
        waitpid(pid, &childExitCode, 0);
        std::cout << "Parent is done. Child process's exit code: "
                  << childExitCode << std::endl;
        if (childExitCode != 0) {
            std::cout << "Child did not exit successfully.\n";
        }
    }
    return 0;  // zero is parent's exit code back to the OS
}
