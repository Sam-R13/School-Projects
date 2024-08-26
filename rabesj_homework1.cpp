// Copyright rabesj
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

// It is ok to use the following namespace delarations in C++ source
// files only. They must never be used in header files.
using namespace std;
using namespace std::string_literals;

/** 
* colToColnum
* @param col - the column we are looking for
* @param headers - the line containing all of the column headers
* @return int - the index of the column we are looking for
* returns -1 if the column is not found
*/
int colToColnum(const std::string& col, std::vector<std::string>& columns) {
    int counter = 0;
    std::string tmp;
    for (std::string& s : columns) {
        if (col == s) {
            return counter;
        }
        counter++;
    }
    return -1;
}

std::vector<std::string> getCols(int index, int argc, char *argv[]) {
    std::vector<std::string> ret;
    for (int i = index + 1; i < argc; i++) {
        ret.push_back(argv[i]);
    }
    return ret;
}

/**
 * getColnums
 * @param index - the starting index for iterating through the args
 * @param argc - the total number of arguments
 * @param argv - the array containing the arguments
 * @return std::vector<int> - a vector containing each column we want to print
 * returns a vector with element 0 = -1 when the arguments cause an error
 */
std::vector<int> getColnums(int index, int argc, char *argv[]) {
    std::vector<int> colnums;
    if (argv[index] == "--colnums"s) {
        for (int i = index + 1; i < argc; i++) {
            colnums.push_back(std::atoi(argv[i]));
        }
    } else if (argv[index] == "--cols"s) {
        std::vector<std::string> cols = getCols(index, argc, argv);
        for (int i = index + 1; i < argc; i++) {
            int tmp = colToColnum(argv[i], cols);
            if (tmp == -1) {
                return { -1 };
            }
            colnums.push_back(index);
        }
    } else {
        return { -1 };
    }
    return colnums;
}

std::vector<std::string> split(std::istringstream& line) {
    std::vector<std::string> ret;
    for (std::string value; line >> std::quoted(value);) {
        ret.push_back(value);
    }
    return ret;
}

void printLine(std::vector<std::string>& vals, std::vector<int>& colnums) {
    for (unsigned int i = 0; i < colnums.size(); i++) {
        if (i > 0) {
            std::cout << "\t";
        }
        std::cout << vals[colnums[i]];
    }
}

void filterCols(std::ifstream& file, std::vector<int>& colnums,
                std::string& filter) {
    std::string line;
    // bool filterFlag = filter == "";
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> vals = split(ss);
        std::cout << std::endl;
        if (vals[colnums[0]].find(filter) != std::string::npos) {
            printLine(vals, colnums);
        }
       // std::cout << line << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // Open file from command line args
    // If file name is incorrect, return error
    std::ifstream file(argv[1]);
    std::string cols, filter;
    if (!file.good()) {
        std::cerr << "Unable to read " << argv[1] << std::endl;
        return 1;
    }

    // Get column headers from file
    while (std::getline(file, cols)) { if (cols != "") { break; } }

    // check for filter command
    // save filter string if necessary
    if (argv[2] == "--filter"s) { filter = argv[3]; }

    // check for cols/colnums command
    // set index to be searched based on filter flag
    // store columns that we would like to print
    int index;
    if (filter == "") { index = 2; } else { index = 4; }
    std::vector<int> colnums = getColnums(index, argc, argv);
    if (colnums[0] == -1) {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }
    std::stringstream ss(cols);
    std::vector<std::string> headerVec;
    for (std::string val; ss >> std::quoted(val);) {
        headerVec.push_back(val);
    }
    printLine(headerVec, colnums);
    filterCols(file, colnums, filter);
    std::cout << std::endl;
    return 0;
}

// End of source code
