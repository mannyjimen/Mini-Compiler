#ifndef _EXPR_
#define _EXPR_

#include "Token.hpp"

#include <string>
#include <vector>
#include <queue>
#include <variant>
#include <iostream>
#include <memory>


class Binary;
class Literal;
class Unary;
class Grouping;
class Variable;
class Expr;
class Assign;
class Logical;

//Visitor interface / abstract class
class ExprVisitor{
public:
    virtual void visit(Binary& binary) = 0;
    virtual void visit(Literal& literal) = 0;
    virtual void visit(Unary& unary) = 0;
    virtual void visit(Grouping& grouping) = 0;
    virtual void visit(Variable& variable) = 0;
    virtual void visit(Assign& assign) = 0;
    virtual void visit(Logical& logical) = 0;
};

//visitor for printing AST of expresssion / Concrete
class AstVisitor : public ExprVisitor {
public:
    void visit(Binary& binary) override;
    void visit(Literal& literal) override;
    void visit(Unary& unary) override;
    void visit(Grouping& grouping) override;

    void parenthesize(const std::string& name, const std::vector<std::shared_ptr<Expr>>& expr_list);

    std::queue<std::string> returns;
};

class AstPrinter : AstVisitor {
public:
    void print(std::shared_ptr<Expr> expr);
};

//Expr interface / abstract class
class Expr{
public: 
    virtual void accept(ExprVisitor& visitor) = 0;
};

struct Binary : public Expr{
    Binary(std::shared_ptr<Expr> left, const Token& op, std::shared_ptr<Expr> right);

    std::shared_ptr<Expr> m_left;
    Token m_op = Token(TokenType::NIL, "NIL", "NIL", 0);
    std::shared_ptr<Expr> m_right;

    void accept(ExprVisitor& visitor) override;
};

struct Literal : public Expr{
    Literal(const LoxObject& lit);

    LoxObject m_lit;

    void accept(ExprVisitor& visitor) override;
};

struct Unary : public Expr{
    Unary(const Token& logicalop, std::shared_ptr<Expr> operand);

    Token m_logicalop = Token(TokenType::NIL, "NIL", "NIL", 0);
    std::shared_ptr<Expr> m_operand;

    void accept(ExprVisitor& visitor) override;
    
};

struct Grouping : public Expr{
    Grouping(std::shared_ptr<Expr> contents);
    std::shared_ptr<Expr> m_contents;

    void accept(ExprVisitor& visitor) override;
};

//accessing var
struct Variable : public Expr{
    Variable(const Token& tokenName);
    Token m_tokenName;

    void accept(ExprVisitor& visitor) override;
};

//assignment expr
struct Assign : public Expr{
    Assign(const Token& tokenName, std::shared_ptr<Expr> value);

    Token m_tokenName;
    std::shared_ptr<Expr> m_value;

    void accept(ExprVisitor& visitor);
};

//logical and / or expr
struct Logical : public Expr {
    Logical(std::shared_ptr<Expr> left_operand, const Token& logical_op, std::shared_ptr<Expr> right_operand);

    std::shared_ptr<Expr> m_left_operand;
    Token m_logical_op;
    std::shared_ptr<Expr> m_right_operand;

    void accept(ExprVisitor& visitor);
};

#endif