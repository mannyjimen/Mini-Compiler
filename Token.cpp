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
    Token(TokenType type, std::string lexeme, std::variant<bool, int, std::string> literal, int line){
        this->m_type = type;
        this->m_lexeme = lexeme;
        this->m_literal = literal;
        this->m_line = line;
    }

    std::string toString(){
        return getTypeString() + " " + m_lexeme + " " + getLiteralString();  
    }

    //convert token type to string
    std::string getTypeString(){
    }

    //convert literal to string
    std::string getLiteralString(){
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

    private:
    TokenType m_type;
    std::string m_lexeme;
    std::variant<bool, int, std::string> m_literal;
    int m_line;
};

#endif