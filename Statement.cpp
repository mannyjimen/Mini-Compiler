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

Var::Var(const Token& token, std::shared_ptr<Expr> expr): m_token{token} {
    m_exprInit = expr;
}

void Var::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}
