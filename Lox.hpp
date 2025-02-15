#ifndef _LOX_
#define _LOX_
#include <fstream>
#include <vector>
#include <iostream>

static bool hadError = false;

class Lox{
    public:
    Lox(int argc, char* argv[]);

    static void error(int line, std::string message);

    private:
    
    static void runPrompt();
    static void runFile(const std::string sourceFileName);

    static void run(const std::string source);
    static void report(int line, std::string where, std::string message);
};

#endif