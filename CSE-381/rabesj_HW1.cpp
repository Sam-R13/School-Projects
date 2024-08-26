/*
 * This program is a homework assignment
 * 
 * Its purpose is to review concepts of C++ from a prerequisite class
 * This program will print employee sales from a file. The file and employee
 * name are supplied as arguments from the command line
 * Copyright 2020 <rabesj@miamioh.edu>
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <string>
#include <limits>

// This alias is mostly to shorten code. The name, strIntMap, simply shows that
// the map uses std::string as its key and int as its value
using strIntMap = std::unordered_map<std::string, int>;

/**
 * This method will populate the unordered_map with the employee records from
 * the file.
 * 
 * @param u This is the unordered_map object that we will be adding to
 * @param is This is a generic input stream for better compatibility, but it
 * will be passed a file stream in this case, connected to the employee sales
 */
void buildMap(strIntMap& u, std::istream& is) {
    // sales will be used to add a value to the map. empName will be used for 
    // the map's key. Word and line will be used to traverse the stream and pass
    // over strings that we don't need
    int sales;
    std::string empName, word, line;
    
    // This while loop will go until getline fails to retrieve anything from the
    // input stream. It will pull from each line, first the employee name, then
    // skip the next string, and then it will pull out the sales, which will
    // be converted and added to the map as a value with the empName as the key
    while (std::getline(is, line)) {
        is >> std::quoted(empName);
        if (empName == "") {
            continue;
        }
        is >> std::quoted(word);
        is >> std::quoted(word);
        sales = std::stoi(word);
        u[empName] += sales;
        empName = "";
    }
}

/**
 * This simple method will check if the employee is found in the map, and
 * either return unsuccessfully or print out the employee's sales
 * 
 * @param name the employee's name that we are searching for
 * @param es the map containing the records of employee sales
 */
void printEmpSales(std::string& name, strIntMap& es) {
    // This if statement checks if the employee's name is found in the map
    if (es.find(name) == es.end()) {
        std::cout << "Employee " << name << " not found." << std::endl;
        return;
    }
    std::cout << "Sales by " << name << " = " << es[name] << std::endl;
}

/**
 * This simple method will iterate over the sales records and find the
 * employee with the best sales. It will print a message showing the employee's
 * name and their sales totals
 * 
 * @param es This is the map that contains the employee sales records
 */
void printMax(strIntMap& es) {
    int max = 0;
    std::string bestSales;
    
    // This range-for will pull each key-value pair into an object that can
    // access both by calling .first for the key and .second for the value
    for (const auto& kv : es) {
        if (kv.second > max) {
            max = kv.second;
            bestSales = kv.first;
        }
    }
    std::cout << "Top employee: " << bestSales << " with sales: " << 
            es[bestSales] << std::endl;
}

/**
 * The main method is where the command line arguments are pulled from, and many
 * of the important objects are initialized
 * 
 * @param argc the number of command line arguments. There should be exactly 4
 * @param argv the command line arguments, provided as an array of C-strings
 *      argv[1]: the input file we are processing
 *      argv[2]: the employee name we are searching for
 *      argv[3]: a boolean value, telling us whether or not to print max sales
 */
int main(int argc, char** argv) {
    // Opening the file for usage, checking if file was properly found
    std::ifstream sales(argv[1]);
    if (!sales.good()) {
        std::cerr << "Unable to retrieve sales data\n";
        return 1;
    }
    
    std::string line;
    
    // Removes all lines of the header; borrowed from exercise1
    while (std::getline(sales, line) && !line.empty() && (line != "\r")) {}
    
    // Declaring the map which will hold employee sales, then sending the file
    // and the map to be populated in buildMap()
    strIntMap employeeSales;
    buildMap(employeeSales, sales);
    
    // Pulling the employee name from command line args; using quoted to format
    // it properly, then sending it to find and print that employee's sales
    std::string empName = argv[2];
    std::quoted(empName);
    printEmpSales(empName, employeeSales);
    
    // The easiest way to convert this string to boolean is to check if the
    // string reads as "true" or "True". Any other value will return a false
    // A more robust solution would be necessary to enable the user to input a
    // single character, or to input 0/1
    std::string s = argv[3];
    if (s == "true" || s == "True") {
        printMax(employeeSales);
    }
    return 0;
}
