#ifndef _TOKEN_
#define _TOKEN_

#include <iostream>
#include <string>
#include <variant>

enum class TokenType{
    //single-char tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    //one or two char tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    //literals
    IDENTIFIER, STRING, NUMBER,

    //keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, ENDOFFILE
};

class Token{
    public:
    Token(TokenType type, std::string lexeme, std::variant<bool, int, std::string> literal, int line){
        this->m_type = type;
        this->m_lexeme = lexeme;
        this->m_literal = literal;
        this->m_line = line;
    }

    std::string toString(){
        return 
    }
    private:
    TokenType m_type;
    std::string m_lexeme;
    std::variant<bool, int, std::string> m_literal;
    int m_line;
};

#endif