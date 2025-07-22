#ifndef _STMT_
#define _STMT_

#include <memory>

#include "Expression.hpp"

//might not need forward declarations. double check
class Expression;
class Print;

//statement visitor interface
class StmtVisitor{
    public:
    virtual void visit(Print& stmt) = 0;
    virtual void visit(Expression& stmt) = 0;  
};

//statement interface
class Stmt {
    public:
    virtual void accept(StmtVisitor& visitor) = 0;
};

//concrete statements
class Expression : public Stmt {
    public:
    Expression(std::shared_ptr<Expr> expr);

    std::shared_ptr<Expr> m_expr;

    void accept(StmtVisitor& visitor) override;

};

class Print : public Stmt {
    public:
    Print(std::shared_ptr<Expr> expr);

    std::shared_ptr<Expr> m_expr;

    void accept(StmtVisitor& visitor) override;
};

#endif