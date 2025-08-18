#include "Statement.hpp"

Expression::Expression(std::shared_ptr<Expr> expr): m_expr(expr) {};
void Expression::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}

Print::Print(std::shared_ptr<Expr> expr): m_expr(expr) {}
void Print::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}

Var::Var(const Token& token, std::shared_ptr<Expr> expr): m_token(token), m_exprInit(expr) {}
void Var::accept(StmtVisitor& visitor){
    visitor.visit(*this);
}

Block::Block(const std::vector<std::shared_ptr<Stmt>>& statements): m_statements(statements) {}
void Block::accept(StmtVisitor& visitor) {
    visitor.visit(*this);
}

IfStmt::IfStmt(const std::shared_ptr<Expr>& conditional,
         const std::shared_ptr<Stmt>& thenBranch,
         const std::shared_ptr<Stmt>& elseBranch):
         m_conditional(conditional), 
         m_thenBranch(thenBranch), 
         m_elseBranch(elseBranch) {}
void IfStmt::accept(StmtVisitor& visitor) {
    visitor.visit(*this);
}
