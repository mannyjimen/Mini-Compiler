#include "Lox.hpp"

//FIX-MAYBE:
//Stubbing all member Tokens since error because Token doesn't
//have default constructor.

struct Expr{
};

struct Binary : public Expr{
    Binary(Expr left, Token op, Expr right){
        m_left = left;
        m_op = op;
        m_right = right;
    }

    Expr m_left;
    Token m_op = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr m_right;
};

struct Literal : public Expr{
    Literal(Token lit){
        m_lit = lit;
    }

    Token m_lit = Token(TokenType::NIL, "NIL", "NIL", 0);
};

struct Unary : public Expr{
    Unary(Token logicalop, Expr operand){
        m_logicalop = logicalop;
        m_operand = operand;
    }

    Token m_logicalop = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr m_operand;
};

struct Grouping : public Expr{
    Grouping(Expr contents){
        m_contents = contents;
    }
    Expr m_contents;
};