//FIX-MAYBE:
//Stubbing all member Tokens since error because Token doesn't
//have default constructor.
#include "Token.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

struct Binary;
struct Literal;
struct Unary;
struct Grouping;
struct Expr;

class Visitor{
public:
    virtual void visit(Binary& binary) = 0;
    virtual void visit(Literal& literal) = 0;
    virtual void visit(Unary& unary) = 0;
    virtual void visit(Grouping& grouping) = 0;
};

//visitor for printing AST of expresssion.
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
    Literal(Token lit);

    Token m_lit = Token(TokenType::NIL, "NIL", "NIL", 0);

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