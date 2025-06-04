#ifndef _PARSER_
#define _PARSER_

#include "Lox.hpp"

#include <vector>

class Parser{
public:
    Parser(std::vector<Token> tokens);

private:
    std::vector<Token>  m_tokens;
    int m_current = 0;

    //checks if the current token matches any of the given types, consumes if so
    bool match(const std::vector<TokenType> types);
    //checks if current token == type (doesnt consume token)
    bool check(const TokenType type) const;
    //returns previous token 
    Token previous() const;
    //consumes token
    Token advance();
    //peeks (returns) next token
    Token peek() const;
    
    bool isAtEnd() const;

    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();

    //error functions
    Token consume(TokenType type, std::string message);
};

#endif