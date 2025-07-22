#include "Statement.hpp"

Expression::Expression(std::shared_ptr<Expr> expr){
    m_expr = expr;
};
void Expression::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}

Print::Print(std::shared_ptr<Expr> expr){
    m_expr = expr;
}
void Print::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}