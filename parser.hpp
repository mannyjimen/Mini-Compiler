#ifndef PARSER_
#define PARSER_

#include "lexer.hpp"

class Parser{

    void parseProgram(std::vector<Token> allTokens);
    std::vector<Token> getTokensForLine(const std::string& line);
};

#endif