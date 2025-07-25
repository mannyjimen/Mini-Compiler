#ifndef _STMT_
#define _STMT_

#include <memory>

#include "Expression.hpp"
#include "Token.hpp"

//might not need forward declarations. double check
class Expression;
class Print;
class Var;

//statement visitor interface
class StmtVisitor{
    public:
    virtual void visit(Print& stmt) = 0;
    virtual void visit(Expression& stmt) = 0;
    virtual void visit(Var& stmt) = 0;
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

#endif