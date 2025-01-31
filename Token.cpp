#ifndef _TOKEN_
#define _TOKEN_

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
    Token(TokenType type, std::string lexeme, std::variant<int, std::string> literal, int line){
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }
    private:
    TokenType type;
    std::string lexeme;
    std::variant<int, std::string> literal;
    int line;
};

#endif