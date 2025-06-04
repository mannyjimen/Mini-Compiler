#ifndef _SCANNER_
#define _SCANNER_

#include "Lox.hpp"

#include <vector>
#include <unordered_map>
#include <string>

class Scanner{

public:
    //hashmap for keywords (reserved words)
    const std::unordered_map<std::string, TokenType> keywords =
    {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"fun", TokenType::FUN},
        {"for", TokenType::FOR},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
    };

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

    //checking if char is alpha, if so, identifier scan
    bool isAlpha(const char& c) const;
    void identifier();

    //checking if alphanumeric character (for identifier post first letter scan)
    bool isAlphaNumeric(const char& c) const;
    
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