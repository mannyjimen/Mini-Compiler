#ifndef _LOX_
#define _LOX_
#include <fstream>
#include <vector>
#include <iostream>

class Lox{
    public:
    Lox(int argc, char* argv[]);

    private:
    
    void runPrompt();
    void runFile(const std::string sourceFileName);

    void run(const std::string source);
};

#endif