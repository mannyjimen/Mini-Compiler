#ifndef _EXPR_
#define _EXPR_

//FIX-MAYBE:
//Stubbing all member Tokens since error because Token doesn't
//have default constructor.
#include "Lox.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <variant>

struct Binary;
struct Literal;
struct Unary;
struct Grouping;
struct Expr;

//Visitor interface / abstract class
class Visitor{
public:
    virtual void visit(Binary& binary) = 0;
    virtual void visit(Literal& literal) = 0;
    virtual void visit(Unary& unary) = 0;
    virtual void visit(Grouping& grouping) = 0;
};

//visitor for printing AST of expresssion / Concrete
class AstVisitor : public Visitor {
public:
    void visit(Binary & binary) override;
    void visit(Literal& literal) override;
    void visit(Unary& unary) override;
    void visit(Grouping& grouping) override;

    void parenthesize(std::string name, std::vector<Expr*> expr_list);

    std::queue<std::string> returns;
};

class AstPrinter : AstVisitor {
public:
    void print(Expr* expr);
};

//Expr interface / abstract class
class Expr{
public: 
    virtual void accept(Visitor& visitor) = 0;
};

struct Binary : public Expr{
    Binary(Expr* left, Token op, Expr* right);

    Expr* m_left;
    Token m_op = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr* m_right;

    void accept(Visitor& visitor) override;
};

struct Literal : public Expr{
    // Literal(bool lit);
    // Literal(double lit);
    // Literal(std::string lit);

    Literal(std::variant<bool, double, std::string> lit);

    std::variant<bool, double, std::string> m_lit;

    void accept(Visitor& visitor) override;
};

struct Unary : public Expr{
    Unary(Token logicalop, Expr* operand);

    Token m_logicalop = Token(TokenType::NIL, "NIL", "NIL", 0);
    Expr* m_operand;

    void accept(Visitor& visitor) override;
    
};

struct Grouping : public Expr{
    Grouping(Expr* contents);
    Expr* m_contents;

    void accept(Visitor& visitor) override;
};

#endif