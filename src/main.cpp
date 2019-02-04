#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../include/scanner.h"
#include "../include/token.h"

void usage();
void run();
void run(const std::string&);
void runFile(const std::string&);

int main(int argc, char* argv[])
{
    if (argc > 2) {
        usage();
        exit(64); // exit code defined in sysexit.h
    }

    if (argc == 2) {
        // script mode
        runFile(argv[1]);
    } else {
        // REPL mode
        run();
    }

    return 0;
}

void usage()
{
    std::cout << "usage: lox-cpp [script]" << std::endl;
}

void run() {
    std::string line;

    while (true) {
        std::cout << "> ";
        if (getline(std::cin, line)) {
            run(line);
        } else {
            break;
        }
    }
}

void run(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanToken();

    #ifdef DEBUG
    for (auto token : tokens) {
        std::cout << token << std::endl;
    }
    #endif
}

void runFile(const std::string& path) {
    std::ifstream is(path);
    std::stringstream buffer;

    buffer << is.rdbuf();

    try {
        run(buffer.str());
    } catch (const std::string& err) {
        std::cerr << "error: " << err << std::endl;
    }
}