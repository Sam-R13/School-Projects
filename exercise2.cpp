/* 
 * File:   exercise2.cpp
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

// A simple type-alias to streamline the code 
using Dictionary = std::unordered_map<std::string, bool>;

/** A simple method to detect if a given word is in the unordered_map 
 *
 */
bool isValid(const Dictionary english, const std::string& word) 
{
	return english.find(word) != std::end(english);
} 

//-------------------------------------------------------------------------
// DO   NOT   MODIFY  CODE  BELOW  THIS  LINE  (but study code below)
//-------------------------------------------------------------------------

/*
 * The main method that loads words from the English dictionary and
 * checks to ensure the words are present in the unordered map.
 */
int main() {
    // Open the file with the list of words.
    std::ifstream wordList("english_5000.txt");
    if (!wordList.good()) {
        std::cerr << "Error opening english_5000.txt\n";
        return 2;
    }
    
    // Load the words from the file into the unordered_map for use
    Dictionary english;
    std::string word;
    while (wordList >> word) {
        english[word] = true;
    }
    
    // Validate that the words can be found in the dictionary.
    for (auto entry : english) {
        isValid(english, entry.first);
    }
    
    // All done!
    return 0;
}
