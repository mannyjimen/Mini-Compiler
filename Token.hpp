#ifndef _TOKEN_
#define _TOKEN_

#include <string>

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

template<typename T>
class Token{
    public:
    Token(TokenType type, std::string lexeme, T literal, int line){
        this->lexemetype = type;
        this->lexemelexeme = lexeme;
        this->literal = literal;
        this->lexemeline = line;
    }
    private:
    const TokenType type;
    const std::string lexeme;
    const T literal;
    const int line;
};

#endif