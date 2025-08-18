#ifndef _LOX_
#define _LOX_

#include "Token.hpp"
#include "Scanner.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "Parser.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

static bool hadError = false;
static bool hadRuntimeError = false;

class Interpreter;
class LoxRuntimeError;

class Lox{

    public:
    Lox(int argc, char* argv[]);

    static Lox& get();

    //static error functions
    static void error(int line, const std::string& message);
    static void error(Token token, const std::string& message);
    static void runtimeError(LoxRuntimeError error);
    static bool isREPL();
    
    private:
    //interpreter declaration
    static Interpreter interpreter;

    private:

    Lox();
    static bool m_repl;

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