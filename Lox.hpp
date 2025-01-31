#ifndef _LOX_
#define _LOX_
#include <fstream>
#include <vector>
#include <iostream>

class Lox{
    public:
    Lox(int argc, char* argv[]);
    bool hadError = false;

    private:
    
    void runPrompt();
    void runFile(const std::string sourceFileName);

    void run(const std::string source);
    
    void error(int line, std::string message);
    void report(int line, std::string where, std::string message);
};

#endif