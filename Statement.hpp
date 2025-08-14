#ifndef _STMT_
#define _STMT_

#include <memory>

#include "Expression.hpp"
#include "Token.hpp"

//need forward declarations
struct Expression;
struct Print;
struct Var;
struct Block;


//statement visitor interface
class StmtVisitor{
    public:
    virtual void visit(Print& stmt) = 0;
    virtual void visit(Expression& stmt) = 0;
    virtual void visit(Var& stmt) = 0;
    virtual void visit(Block& stmt) = 0;
};

//statement interface
class Stmt {
    public:
    virtual void accept(StmtVisitor& visitor) = 0;
};

//concrete statements
struct Expression : public Stmt {
    Expression(std::shared_ptr<Expr> expr);

    std::shared_ptr<Expr> m_expr;

    void accept(StmtVisitor& visitor) override;

};

//print statement
struct Print : public Stmt {
    Print(std::shared_ptr<Expr> expr);

    std::shared_ptr<Expr> m_expr;

    void accept(StmtVisitor& visitor) override;
};

//decl var
struct Var : public Stmt {
    Var(const Token& token, std::shared_ptr<Expr> expr);

    Token m_token;
    std::shared_ptr<Expr> m_exprInit;

    void accept(StmtVisitor& visitor) override;
};

//block statement
struct Block : public Stmt {
    Block(const std::vector<std::shared_ptr<Stmt>>& statements);

    std::vector<std::shared_ptr<Stmt>> m_statements;

    void accept(StmtVisitor& visitor) override;
};

#endif