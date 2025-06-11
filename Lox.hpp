#ifndef _LOX_
#define _LOX_

#include "Token.hpp"
#include "Scanner.hpp"
#include "ExpressionTypes.hpp"
#include "Parser.hpp"

#include <fstream>
#include <iostream>
#include <string>

static bool hadError = false;

class Lox{
    public:
    //constructor
    Lox(int argc, char* argv[]);

    //static error function
    static void error(int line, const std::string& message);
    static void error(Token token, const std::string& message);


    private:
    //run from prompt
    static void runPrompt();
    //run from file
    static void runFile(const std::string& sourceFileName);
    //run line
    static void run(const std::string& source);

    //error helper
    static void report(int line, const std::string& where, const std::string& message);
};

#endif