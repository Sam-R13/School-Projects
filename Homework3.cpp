/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "Movie.h"

using namespace std;

// A shortcut to a map of Movies. The key into this map is the 
// Movie's unique ID
using MovieMap = std::unordered_map<int, Movie>;

/**
 * Method to read Movie entries from a given file into an 
 * unordered map.
 * 
 * @param filePath Path to the file from where data is to be read.
 * 
 * @return An unordered map containing the data.
 */
MovieMap load(const std::string& filePath) {
    // Create the map to be populated and returned
    MovieMap db;
    // Create the entry for the file to be read
    std::ifstream data(filePath);
    if (!data.good()) {
        throw std::runtime_error("Unable to read file " + filePath);
    }
    // Read and ignore the first comment-line
    std::string header;
    std::getline(data, header);
    // Load movie information into the DB by reading 
    // entry-by-entry and then add them to the unordered_map using
    // operator[]
    Movie m;
    while (data >> m) {
        // Store the person information into our map.
        const int id = m.getID();
        db[id] = m;
    }
    // Return the map of people back
    return db;
}

/**
 * Read ID and print information about a movie, if the ID is valid.
 * 
 * This method uses the find method in unordered_map to quickly
 * find if the ID is valid. Note that the find method can be used
 * only to search based on the key/index (or "first") for the
 * unordered_map.  This method has O(1) time complexity!
 * 
 * @param db The unordered_map of movies to be used by this method.
 * 
 * @param id The ID of the movie to be found and printed.
 */
void find(const MovieMap& db, const int id) {
    // Use the find method to find entry and print it.
    if (db.find(id) != db.end()) {
        std::cout << db.at(id) << std::endl;
    } else {
        std::cout << "Movie with ID " << id << " not found in database.\n";
    }
}

/**
 * This method search for a given sub-string in all movie entries
 * and prints matching entries. Since this method has to iterate
 * over each entry it has a O(n) time complexity.
 * 
 * @param db The unordered_map of people to be used by this method.
 * 
 * @param searchStr The sub-string to search for.
 */
void search(const MovieMap& db, const std::string& searchStr) {
    // Search the full info of a person to see if data is in there.
    // use the range-based for loop (as discussed in lecture slides)!
    int count = 0;
    for (const auto entry : db) {
        // Get the string form of the person's information.
        const std::string info = to_string(entry.second);
        // Check to see if the info contains the search terms
        if (info.find(searchStr) != std::string::npos) {
            std::cout << entry.second << std::endl;
            count++;
        }
    }
    // Print the matching counts.
    std::cout << "Found " << count << " matche(s).\n";
}

/*
 * A simple main method to load and list of movies into a given 
 */
int main(int argc, char** argv) {
    // First load the person database from a given file.
    MovieMap db = load("movies_db.txt");
    std::string cmd;  // The command to process
    // Repeatedly process command, until user enters exit.
    while (std::cout << "Enter a command:\n",
           std::cin >> cmd && (cmd != "exit")) {
        // Process the command appropriately.
        if (cmd ==  "find") {
            int id;
            std::cin >> id;     // Get movie ID.
            std::cin.ignore();  // Ignore new-line due to integer reading.
            find(db, id);       // Check and print movie information.
        } else if (cmd == "search") {
            std::string searchTerm;
            std::cin >> std::quoted(searchTerm);  // Read search string.
            search(db, searchTerm);               // Perform the search.
        } 
    }

    // All one.
    return 0;
}

