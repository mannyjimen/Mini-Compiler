#include "Token.hpp"

Token::Token(TokenType type, std::string lexeme, std::variant<bool, int, std::string> literal, int line){
    this->m_type = type;
    this->m_lexeme = lexeme;
    this->m_literal = literal;
    this->m_line = line;
}

std::string Token::toString(){
    return getTypeString() + " " + m_lexeme + " " + getLiteralString();  
}

std::string Token::getTypeString(){
    switch(this->m_type){
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::DOT:
            return "DOT";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::SLASH:
            return "SLASH";
        case TokenType::STAR:
            return "STAR";
        case TokenType::BANG:
            return "BANG";
        case TokenType::BANG_EQUAL:
            return "BANG_EQUAL";
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case TokenType::GREATER:
            return "GREATER";
        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case TokenType::LESS:
            return "LESS";
        case TokenType::LESS_EQUAL:
            return "LEFT_BRACE";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::STRING:
            return "STRING";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::AND:
            return "AND";
        case TokenType::CLASS:
            return "CLASS";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::FALSE:
            return "FALSE";
        case TokenType::FUN:
            return "FUN";
        case TokenType::FOR:
            return "FOR";
        case TokenType::IF:
            return "IF";
        case TokenType::NIL:
            return "NIL";
        case TokenType::OR:
            return "OR";
        case TokenType::PRINT:
            return "PRINT";
        case TokenType::RETURN:
            return "RETURN";
        case TokenType::SUPER:
            return "SUPER";
        case TokenType::THIS:
            return "THIS";
        case TokenType::TRUE:
            return "TRUE";
        case TokenType::VAR:
            return "VAR";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::ENDOFFILE:
            return "ENDOFFILE";
        default:
            return "undefined";
    }
}

std::string Token::getLiteralString(){
    if (std::get_if<bool>(&m_literal)){
        if (std::get<bool>(m_literal) == 0)
            return "0";
        else
            return "1";
    }
    else if (std::get_if<int>(&m_literal)){
        return std::to_string(std::get<int>(m_literal));
    }
    //if literal is string
    return std::get<std::string>(m_literal);

}