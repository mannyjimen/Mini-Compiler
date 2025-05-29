//FIX-MAYBE:
//Stubbing all member Tokens since error because Token doesn't
//have default constructor.
#include "Token.hpp"
#include "AstPrinter.hpp"

#include <iostream>
#include <string>
#include <vector>

struct Binary;
struct Literal;
struct Unary;
struct Grouping;
struct Expr;
class AstVisitor;

struct Expr{
    virtual std::string acceptAstPrint(AstVisitor visitor) = 0;
};

struct AstVisitor{
    std::string visitBinary(Binary& binary);
    std::string visitLiteral(Literal& literal);
    std::string visitUnary(Unary& unary);
    std::string visitGrouping(Grouping& grouping);

    std::string parenthesize(std::string name, std::vector<Expr*> expr_list);
};

class AstPrinter : public AstVisitor{
public:
    std::string print(Expr* expr){
        return expr->acceptAstPrint(*this);
    }
};

struct Binary : public Expr{
    Binary(Expr* left, Token op, Expr* right);

    Expr* m_left;
    Token m_op = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr* m_right;

    std::string acceptAstPrint(AstVisitor visitor) override{
        return visitor.visitBinary(*this);
    }

};

struct Literal : public Expr{
    Literal(Token lit);

    Token m_lit = Token(TokenType::NIL, "NIL", "NIL", 0);

    std::string acceptAstPrint(AstVisitor visitor) override{
        return visitor.visitLiteral(*this);
    }
};

struct Unary : public Expr{
    Unary(Token logicalop, Expr* operand);

    Token m_logicalop = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr* m_operand;

    std::string acceptAstPrint(AstVisitor visitor) override{
        return visitor.visitUnary(*this);
    }
};

struct Grouping : public Expr{
    Grouping(Expr* contents);
    Expr* m_contents;

    std::string acceptAstPrint(AstVisitor visitor) override{
        return visitor.visitGrouping(*this);
    }
};