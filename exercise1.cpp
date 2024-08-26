/**
 * Copyright 2020 <raodm@miamioh.edu>
 * A program to demonstrate:
 *   1. Structuring logic to be algorithmic & type-agnostic
 *      (as much as possible)
 *   2. Demonstrating the advantages of working with generic I/O streams
 *      2.1. Use standard I/O streams (std::cin, std::cout)
 *      2.2. Use file I/O stream (std::ifstream) 
 *
 */

#include <string>
#include <iostream>
#include <fstream>

// A convenience data type used in the printMax method below. Such
// type aliases are used to improve readability of code, streamline
// algorithmic thinking, and ease code maintenance.
using InputType = int;

/**
 * Method to print the maximum value of a given type. Inputs are read
 * from a given input stream.  This method assumes that there is at
 * least 1 valid input in the given input stream.  Moreover, it
 * assumes that the data in the input stream is compatible with
 * InputType.  The result is printed to a given output stream.
 *
 * @param is The input stream from where input values are to be
 * read. Inputs are read until end-of-file is reached.  The default
 * stream is std::cin (type Control+D to input logical end-of-file).
 *
 * @param os The output stream to where maximum value is to be
 * written.  The default stream is std::cout.
 */
void printMax(std::istream& is = std::cin, std::ostream& os = std::cout) {
    // Intermediate variables 
    InputType input, max;
    // Setup the first input as the current maximum
    is >> max;
    
    // Process inputs from the given input stream
    while (is >> input) {
        // Track the maximum input we have observed so far.
        if (input > max) {
            max = input;  // found new maximum value.
    }
}
    
    // Print the maximum value to the specified output stream.
    os << "Maximum value = " << max << std::endl;
}


int main(int argc, char *argv[]) {
    //---------------------------------------------------------------
    // Instead of reading numbers from standard input (i.e.,
    // std::cin), here we read numbers from an input file.
    std::cout << "Processing data from: " << argv[1] << std::endl;
    std::ifstream inputs(argv[1]);  // input  file stream

    // Skip over the headers at the beginning of the data file
    std::string line;

    // Note that we check for "\r" because HTTP headers end with "\r\n" and
    // std::getline will only remove "\n" and not "\r". So a blank line can
    // be either blank or just have  a "\r"
    while (std::getline(inputs, line) && !line.empty() && (line != "\r")) {}

    // Now, Have the helper method process the data for us
    printMax(inputs, std::cout);
    
    return 0;
}
