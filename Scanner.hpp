#ifndef _SCANNER_
#define _SCANNER_

#include "Lox.hpp"
#include "Token.hpp"

#include <array>
#include <unordered_map>
#include <vector>
#include <map>

class Scanner{
    std::string m_source;
    std::vector<Token*> m_tokens;
    int m_start = 0;
    int m_current = 0;
    int m_line = 1;

    Scanner(std::string source);
    std::vector<Token*> scanTokens();
    //token scanning 
    void scanToken();
    char advance();
    //helper functions
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<bool, int, std::string> literal);

    //checks if scanner is at end of source
    bool isAtEnd();
};

#endif