/*
 * This program is designed to take linux user and group input, parse the input
 * into maps, then match up user information with the group information
 * 
 * Copyright 2020 <rabesj@miamioh.edu>
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

// These aliases make the code much cleaner, and allow me to use less space in
// method declarations. The naming is straightforward
using intVecMap = std::unordered_map<int, std::vector<std::string>>;
using intStrMap = std::unordered_map<int, std::string>;

/**
 * This method populates a map with user information, with the key being the uid
 * and the value being the loginID
 * 
 * @param u the map that we are populating with user data
 * @param is the input stream that we are obtaining the user data from. It is 
 * generic for better compatibility, but it will almost always be accepting a
 * file stream
 */
void addUsers(intStrMap& u, std::istream& is) {
    int uid;
    std::string loginID, word;
    
    /*
     * This while loop checks for eof. It uses the delim variant of std::getline
     * to pull each individual word from the input stream. It saves the ones we
     * want (loginID, and uid), and tosses everything else.
     */
    while (!is.eof()) {
        std::getline(is, loginID, ':');
        std::getline(is, word, ':');
        std::getline(is, word, ':');
        uid = std::stoi(word);
        // This if statement protects against an error that caused the last map
        // object to be overwritten, since the last line before the eof is blank
        if (loginID.empty()) {
            break;
        }
        u[uid] = loginID;
        std::getline(is, word);
    }   
}

/**
 * This method populates a map with group data, with the key being the gid, and
 * the value being a vector of members. Each member's information is added using
 * the information from the user information records.
 * 
 * @param g the map of group data that we are populating
 * @param u the map of user data which we are using to populate the group map
 * @param is the input stream that we are using to obtain the group data
 */
void makeGroups(intVecMap& g, intStrMap& u, std::istream& is) {
    int gid, uid;
    std::string groupID, word, line;
    // this while loop checks for eof. while eof is not found, it pulls data
    // from the input stream and pushes the important data into the group map
    while (!is.eof()) {
        std::getline(is, line);
        // This if statement prevents against an error that caused the last map
        // object to be overwritten
        if (line.empty()) {
            break;
        }
        std::replace(std::begin(line), std::end(line), ':', ' ');
        std::replace(std::begin(line), std::end(line), ',', ' ');
        std::istringstream lineis(line);
        std::vector<std::string> members;
        lineis >> groupID;
        members.push_back(groupID);
        lineis >> word;
        lineis >> word;
        gid = std::stoi(word);
        // This while loop populates the vectors that will be added to the group
        // map
        while (lineis >> word) {
            uid = std::stoi(word);
            members.push_back(u[uid] + "(" + word + ")");
        }
        g[gid] = members;
    }
}

/**
 * This method formats the groups for clean printing through the console
 * 
 * @param gid this is the integer value of the groupid that we are trying to
 * print
 * @param g this is the map that contains all of the group data
 */
void printGroup(int gid, intVecMap& g) {
    // This if statement checks to see if there is a group with a key of gid in
    // the group map
    if (g.find(gid) == g.end()) {
        std::cout << gid << " = Group not found." << std::endl;
        return;
    }
    // The first value of each group's vector is the group name i.e. root, labs
    // etc. This simple save allows us to print the group's name using slightly
    // different formatting, remove it from the vector, and print the rest of
    // the vector off a range for loop. Then, when printing is finished, we add
    // the group's name back to the beginning of the vector
    std::string tmp = g[gid].front();
    std::cout << gid << " = " << tmp << ":";
    g[gid].erase(g[gid].begin());
    for (std::string s : g[gid]) {
        std::cout << " " << s;
    }
    g[gid].insert(g[gid].begin(), tmp);
    std::cout << std::endl;
}

/**
 * This main method declares and initializes several of the most important
 * objects we use in this program, and receives command line arguments that we
 * will parse and respond to
 * 
 * @param argc the number of arguments passed. This can be any number, and we
 * check it in order to run our loops properly
 * @param argv an array of C-strings, containing the actual arguments passed
 *      argv[from 1 to i]: a number, representing the gid to search for & print
 */
int main(int argc, char** argv) {
    // Initialize the file streams based on predetermined files
    // Check if the file streams were opened properly, throw an error if not
    std::ifstream passwd("passwd");
    if (!passwd.good()) {
        std::cerr << "Unable to retrieve password file\n";
        return 1;
    }
    std::ifstream groupsFile("groups");
    if (!groupsFile.good()) {
        std::cerr << "Unable to retrieve groups file\n";
        return 1;
    }
    
    intStrMap users;
    addUsers(users, passwd);
    
    intVecMap groupsMap;
    makeGroups(groupsMap, users, groupsFile);
    
    // This loop will take in each argument from argv[1] to argv[argc - 1]
    // This ensures that the program can handle any number of arguments passed
    // from the user
    int id;
    for (int i = 1; i < argc; i++) {
        id = atoi(argv[i]);
        printGroup(id, groupsMap);
    }
    return 0;
}
