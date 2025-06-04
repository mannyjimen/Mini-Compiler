#include "Parser.hpp"
//CONSTRUCTION OF TREE. Making sure grammar is good, and constructing
//AST out of all these tokens!

bool Parser::match(const std::vector<TokenType> types){
    for (const TokenType& type: types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
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
    return m_tokens[m_current];
}

Token Parser::previous() const{
    return m_tokens[m_current - 1];
}

bool Parser::isAtEnd() const{
    return peek().m_type == TokenType::ENDOFFILE;
}

Expr* Parser::expression(){
    return equality();
}

Expr* Parser::equality(){
    //equality -> comparison( ("!=" | "==") comparison )*
    //comparison...
    Expr* expr = comparison();

    //...(("!="|"==")comparison)*
    while(match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})){
        Token op = previous();
        Expr* right = comparison(); //parsing the next (...)*
        expr = new Binary(expr, op, right); //appending to expr
    }

    return expr;
}

Expr* Parser::comparison(){
    //comparison -> term( ( ">" | ">=" | "<" | "<=") term )*
    Expr* expr = term();

    while(match({TokenType::LESS, TokenType::LESS_EQUAL
        ,TokenType::GREATER, TokenType::GREATER_EQUAL})){
        Token op = previous();            
        Expr* right = term();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::term(){
    Expr* expr = factor();

    while(match({TokenType::PLUS, TokenType::MINUS})){
        Token op = previous();            
        Expr* right = factor();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::factor(){
    Expr* expr = unary();

    while(match({TokenType::STAR, TokenType::SLASH})){
        Token op = previous();            
        Expr* right = unary();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::unary(){
    //unary -> ("!"|"-") unary | primary
    if (match({TokenType::MINUS, TokenType::BANG})){
        Token op = previous();
        Expr* right = unary();
        return new Unary(op, right);
    }
    return primary();
}

Expr* Parser::primary(){
    if (match({TokenType::FALSE})) return new Literal(false);
    if (match({TokenType::TRUE})) return new Literal(true);
    //FIX: Might have to rework how null/nil works
    if (match({TokenType::NIL})) return new Literal("NIL");
    if (match({TokenType::NUMBER, TokenType::STRING})){
        return new Literal(previous().m_literal);
    }

    //grouping case 
    if (match({TokenType::LEFT_PAREN})){
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }
}