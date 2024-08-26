/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Movie.h"

// The default (and only) constructor for this class.
Movie::Movie() {
    // The instance variables are initialized in the header file. Consequently,
    // this constructor is empty.
}

// The destructor
Movie::~Movie() {
    // Currently, the destructor does not have any special tasks to do.
}

// Stream-extraction operator.
std::istream& operator>>(std::istream& is, Movie& m) {
    // Read the values from an entry in the stream/file in the correct order.
    is >> m.movieID >> std::quoted(m.title) >> m.year >> std::quoted(m.genres)
       >> m.imdbId  >> m.rating >> m.numRaters;
    // Return the stream as per the API requirement.
    return is;
}

// The stream insertion operator.
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    // Read the values from an entry in the stream/file in the correct order.
    os << m.movieID << " " << std::quoted(m.title) << " " << m.year   << " " 
       << std::quoted(m.genres) << " " << m.imdbId << " " << m.rating << " "
       << m.numRaters;
    // Return the stream as per the API requirement.
    return os;    
}

// A simple to-string method.
std::string to_string(const Movie& m) {
    std::ostringstream os;
    os << m;
    return os.str();
}

#endif

