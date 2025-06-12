#include "Parser.hpp"
/*CONSTRUCTION OF TREE. Making sure grammar is good, and constructing
AST out of all these tokens!*/

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens){
    m_tokens = tokens;
}

bool Parser::match(const std::vector<TokenType> types){
    for (const TokenType& type: types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(const TokenType& type, const std::string& message){
    if(check(type)) return advance();
    //throwing ParseError, will be caught in parse()
    throw error(peek(), message);
}

Token Parser::advance(){
    if (!isAtEnd()) m_current++;
    return previous();
}

bool Parser::check(TokenType type) const{
    if (isAtEnd()) return false;
    return peek().m_type == type;
}

Token Parser::peek() const{
    return *m_tokens[m_current];
}

Token Parser::previous() const{
    return *m_tokens[m_current - 1];
}

bool Parser::isAtEnd() const{
    return peek().m_type == TokenType::ENDOFFILE;
}

std::shared_ptr<Expr> Parser::parse(){
    try{
        return expression();
    } catch (ParseError error){
        return nullptr;
    }
}

std::shared_ptr<Expr> Parser::expression(){
    return equality();
}

std::shared_ptr<Expr> Parser::equality(){
    //equality -> comparison( ("!=" | "==") comparison )*
    //comparison...
    std::shared_ptr<Expr> expr = comparison();

    //...(("!="|"==")comparison)*
    while(match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})){
        Token op = previous();
        std::shared_ptr<Expr> right = comparison(); //parsing the next (...)*
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right)); //appending to expr
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison(){
    //comparison -> term( ( ">" | ">=" | "<" | "<=") term )*
    std::shared_ptr<Expr> expr = term();

    while(match({TokenType::LESS, TokenType::LESS_EQUAL
        ,TokenType::GREATER, TokenType::GREATER_EQUAL})){
        Token op = previous();            
        std::shared_ptr<Expr> right = term();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term(){
    std::shared_ptr<Expr> expr = factor();

    while(match({TokenType::PLUS, TokenType::MINUS})){
        Token op = previous();            
        std::shared_ptr<Expr> right = factor();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor(){
    std::shared_ptr<Expr> expr = unary();

    while(match({TokenType::STAR, TokenType::SLASH})){
        Token op = previous();            
        std::shared_ptr<Expr> right = unary();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary(){
    //unary -> ("!"|"-") unary | primary
    if (match({TokenType::MINUS, TokenType::BANG})){
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::shared_ptr<Unary>(new Unary(op, right));
    }
    return primary();
}

std::shared_ptr<Expr> Parser::primary(){
    if (match({TokenType::FALSE})) return std::shared_ptr<Literal>(new Literal(false));
    if (match({TokenType::TRUE})) return std::shared_ptr<Literal>(new Literal(true));
    //FIX: Might have to rework how null/nil works
    if (match({TokenType::NIL})) return std::shared_ptr<Literal>(new Literal("NIL"));
    if (match({TokenType::NUMBER, TokenType::STRING})){
        return std::shared_ptr<Literal>(new Literal(previous().m_literal));
    }

    //grouping case 
    if (match({TokenType::LEFT_PAREN})){
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::shared_ptr<Grouping>(new Grouping(expr));
    }

    throw error(peek(), "Expect expression.");
}

//Error function implementations

ParseError Parser::error(const Token& token, const std::string& message){
    Lox::error(token, message);
    ParseError signal; return signal;
}

void Parser::synchronize(){
    //currently at broken token, going to move forward once.
    advance();

    while(!isAtEnd()){
        //checking if we are at the start of a statement
        //PROBABLY starting a new statement (not guaranteed)
        if(previous().m_type == TokenType::SEMICOLON) return;
        switch(peek().m_type){
            case TokenType::RETURN:
            case TokenType::PRINT:
            case TokenType::FOR:
            case TokenType::WHILE:
            case TokenType::IF:
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
                return;
        }
        //discarding token
        advance();
    }
}