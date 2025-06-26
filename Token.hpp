#ifndef _TOKEN_
#define _TOKEN_

#include <string>
#include <variant>

using LoxObject = std::variant<std::monostate, bool, double, std::string>;

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
    //parameterized constructor for token
    Token(TokenType type, const std::string& lexeme, LoxObject literal, int line);
    //convert token to string
    std::string toString() const;
    //converts token type to string (helper for toString)
    std::string getTypeString() const;
    //converts token literal to string (helper for toString)
    std::string getLiteralString() const;
    //returns lexeme of token
    std::string getLexeme() const;

    TokenType m_type;
    std::string m_lexeme;
    LoxObject m_literal;
    int m_line;
};

#endif