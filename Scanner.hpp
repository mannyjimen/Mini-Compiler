#ifndef _SCANNER_
#define _SCANNER_

#include "Lox.hpp"
#include "Token.hpp"

#include <vector>

class Scanner{

public:
    //scanner constructor
    Scanner(const std::string& source);
    //scanning entire source
    std::vector<Token*> scanTokens();
    //scanning individual lexemes
    void scanToken();
    
    //consume next char in source
    char advance();
    //return whether next char is expected char
    bool match(const char& expected);
    char peek() const;
    char peekNext() const;

    //string scan
    void string();
    //checking digit, if so, number scan
    bool isDigit(const char& c) const;
    void number();
    
    //addTokens
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<bool, double, std::string> literal);

    //checks if scanner is at end of source
    bool isAtEnd() const;

    //prints every token in m_tokens (helper function)
    void printTokens() const;

private:
    std::string m_source;
    std::vector<Token*> m_tokens;
    int m_start = 0;
    int m_current = 0;
    int m_line = 1;
};

#endif