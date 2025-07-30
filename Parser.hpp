#ifndef _PARSER_
#define _PARSER_

#include "Expression.hpp"
#include "Statement.hpp"
#include "Lox.hpp"

#include <vector>
#include <string>
#include <memory>

class ParseError{
};

class Parser{
public:
    Parser(const std::vector<std::shared_ptr<Token>> tokens);
    //initial, main method
    std::vector<std::shared_ptr<Stmt>> parse();

private:
    std::vector<std::shared_ptr<Token>>  m_tokens;
    int m_current = 0;

    //checks if the current token matches any of the given types, consumes if so
    bool match(const std::vector<TokenType> types);
    Token consume(const TokenType& type, const std::string& message);
    //checks if current token == type (doesnt consume token, for match/consume)
    bool check(const TokenType type) const;
    //returns previous token 
    Token previous() const;
    //consumes token
    Token advance();
    //peeks (returns) next token
    Token peek() const;
    
    bool isAtEnd() const;

    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> assignment();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();

    std::shared_ptr<Stmt> declaration();
    std::shared_ptr<Stmt> declVar();
    std::shared_ptr<Stmt> statement();
    std::shared_ptr<Stmt> expressionStatement();
    std::shared_ptr<Stmt> printStatement();
    
    //error functions
    static ParseError error(const Token& token, const std::string& message);
    void synchronize();
};

#endif