#ifndef _SCANNER_
#define _SCANNER_

#include "Lox.hpp"
#include "Token.hpp"

#include <array>
#include <unordered_map>
#include <vector>
#include <map>

class Scanner{

public:
    //scanner constructor
    Scanner(std::string source);
    //scanning entire source
    std::vector<Token*> scanTokens();
    //scanning individual lexemes
    void scanToken();
    
    //consume next char in source
    char advance();
    //return whether next char is expected char
    bool match(char expected);
    char peek();

    //string scan
    void string();
    
    //addTokens
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<bool, int, std::string> literal);

    //checks if scanner is at end of source
    bool isAtEnd();

    //prints every token in m_tokens (helper function)
    void printTokens();

private:
    std::string m_source;
    std::vector<Token*> m_tokens;
    int m_start = 0;
    int m_current = 0;
    int m_line = 1;
};

#endif