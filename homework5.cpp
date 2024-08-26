/* 
 * Copyright 2020 rabesj@miamioh.edu
 * A simple web-server.  
 * 
 * The web-server performs the following tasks:
 * 
 *     1. Accepts connection from a client.
 *     2. Processes cgi-bin GET request.
 *     3. If not cgi-bin, it responds with the specific file or a 404.
 * 
 */

#include <ext/stdio_filebuf.h>
#include <unistd.h>
#include <sys/wait.h>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

// Using namespaces to streamline code below
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using StrVec = std::vector<std::string>;

/** Forward declaration for method defined further below.  You will
    need to use this url_decode method in your serveClient method.
 */
std::string url_decode(std::string data);

// Named-constants to keep pipe code readable below
const int READ = 0, WRITE = 1;

/**
 * This is a simple method to check if a request is valid or not
 * i.e. does it start with "/cgi-bin/exec"
 * @param getReq the request to be checked
 * @return true if request valid, false otherwise
 */
bool checkValid(std::string& getReq) {
    return (getReq.rfind("/cgi-bin/exec", 0) == 0);
}

/**
 * This method goes through the process of a sending a 404 error in the case of
 * a bad request
 * @param os a generic output stream for better compatitibility
 * @param badRequest the string containing the bad request to print back to the
 * user
 */
void send404(std::ostream& os, std::string& badRequest) {
    badRequest = badRequest.substr(1);
    std::string line = "Invalid request: " + badRequest;
    os << "HTTP/1.1 404 Not Found\r\n"
       << "Content-Type: text/plain\r\n"
       << "Transfer-Encoding: chunked\r\n"
       << "Connection: Close\r\n"
       << "\r\n"
       << std::hex << line.size() + 1 << "\r\n"
       << line << "\r\n"
       << "\r\n0\r\n\r\n";
}

/**
 * This helper method processes a request for checking and other manipulation
 * @param s the request to be processed
 * @return the processed request
 */
std::string processReq(std::string& s) {
    std::stringstream ss(s);
    std::string word;
    ss >> std::quoted(word);
    ss >> std::quoted(word);
    return word;
}

/**
 * This method parses the command and arguments from a request
 * @param line the request line to be parsed
 * @return simply the command and arguments, parsed from the longer request
 */
std::vector<char*> getCmd(std::string& line) {
    int cmdPos = line.find("cmd") + 4;
    int cmdLength = line.find('&') - cmdPos;
    std::string cmd = line.substr(cmdPos, cmdLength);
    int argsPos = line.find("args") + 5;
    int argsLength = line.find("HTTP/1.1") - argsPos;
    std::string args = line.substr(argsPos, argsLength);
    line = cmd + " " + args;
    std::stringstream ss(line);
    std::vector<char*> argList;
    StrVec passThrough;
    std::string word;
    while (ss >> std::quoted(word)) {
        passThrough.push_back(word);
    }
    for (auto& s : passThrough) {
        argList.push_back(&s[0]);
    }
    argList.push_back(nullptr);
    return argList;
}

/**
 * This method writes a header and chunk data to the output stream
 * @param os generic output stream for better compatibility. Used to send data
 * to user or browser client
 * @param is generic input stream for better compatibility. Some data is pulled
 * from this input stream, and formatted to be sent out
 */
void writeData(std::ostream& os, std::istream& is) {
    os << "HTTP/1.1 200 OK\r\n"
       << "Content-Type: text/plain\r\n"
       << "Transfer-Encoding: chunked\r\n"
       << "Connection: Close\r\n";
    for (std::string line; std::getline(is, line);) {
            line += "\n";
            os << "\r\n";
            os << std::hex << line.size() << "\r\n";
            os << line;
        }
}

/**
 * This method is a larger helper method that runs a lot of our other smaller
 * methods. It does a lot of the work for this program
 * @param request The request line sent by the user
 * @param os generic output stream for better compatibility. This stream will
 * display data to the user
 */
void runCmds(std::string& request, std::ostream& os) {
    std::vector<char*> args = getCmd(request);
    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[READ]);
        dup2(pipefd[WRITE], WRITE);
        execvp(args[0], &args[0]);
    } else {
        close(pipefd[WRITE]);
        __gnu_cxx::stdio_filebuf<char> fb(pipefd[READ], std::ios::in, 1);
        std::istream is(&fb);
        writeData(os, is);
        int exitCode = 0;
        waitpid(pid, &exitCode, 0);
        std::string line = "Exit code: " + std::to_string(exitCode);
        os << "\r\n" << std::hex << line.size() << "\r\n" << line << "\r\n";
        os << "0\r\n\r\n";
    }
}

/**
 * Process HTTP request (from first line & headers) and
 * provide suitable HTTP response back to the client.
 * 
 * @param is The input stream to read data from client.
 * @param os The output stream to send data to client.
 */
void serveClient(std::istream& is, std::ostream& os) {
    // Implement this method as per homework requirement. Obviously
    // you should be thinking of structuring your program using helper
    // methods first. You should add comments to your helper methods
    // and then go about implementing them.
    std::string line;
    std::getline(is, line);
    line = url_decode(line);
    std::string request = processReq(line);
    if (!checkValid(request)) {
        send404(os, request);
    } else {
       runCmds(line, os);
    }
}

// -----------------------------------------------------------
//       DO  NOT  ADD  OR MODIFY CODE BELOW THIS LINE
// -----------------------------------------------------------

/** Convenience method to decode HTML/URL encoded strings.

    This method must be used to decode query string parameters
    supplied along with GET request.  This method converts URL encoded
    entities in the from %nn (where 'n' is a hexadecimal digit) to
    corresponding ASCII characters.

    \param[in] str The string to be decoded.  If the string does not
    have any URL encoded characters then this original string is
    returned.  So it is always safe to call this method!

    \return The decoded string.
*/
std::string url_decode(std::string str) {
    // Decode entities in the from "%xx"
    size_t pos = 0;
    while ((pos = str.find_first_of("%+", pos)) != std::string::npos) {
        switch (str.at(pos)) {
            case '+': str.replace(pos, 1, " ");
            break;
            case '%': {
                std::string hex = str.substr(pos + 1, 2);
                char ascii = std::stoi(hex, nullptr, 16);
                str.replace(pos, 3, 1, ascii);
            }
        }
        pos++;
    }
    return str;
}

/**
 * Runs the program as a server that listens to incoming connections.
 * 
 * @param port The port number on which the server should listen.
 */
void runServer(int port) {
    io_service service;
    // Create end point
    tcp::endpoint myEndpoint(tcp::v4(), port);
    // Create a socket that accepts connections
    tcp::acceptor server(service, myEndpoint);
    std::cout << "Server is listening on port "
              << server.local_endpoint().port() << std::endl;
    // Process client connections one-by-one...forever
    while (true) {
        tcp::iostream client;
        // Wait for a client to connect
        server.accept(*client.rdbuf());
        // Process information from client.
        serveClient(client, client);
    }
}

/*
 * The main method that performs the basic task of accepting connections
 * from the user.
 */
int main(int argc, char** argv) {
    if (argc == 2) {
        // Process 1 request from specified file for functional testing
        std::ifstream input(argv[1]);
        serveClient(input, std::cout);
    } else {
        // Run the server on some available port number.
        runServer(0);
    }
    return 0;
}

// End of source code
