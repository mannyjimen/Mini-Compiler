#ifndef _LOX_
#define _LOX_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

static bool hadError = false;

class Lox{
    public:
    //constructor
    Lox(int argc, char* argv[]);

    //static error function
    static void error(int line, std::string message);

    private:
    //run from prompt
    static void runPrompt();
    //run from file
    static void runFile(const std::string sourceFileName);
    //run line
    static void run(const std::string source);

    //error helper
    static void report(int line, std::string where, std::string message);
};

#endif