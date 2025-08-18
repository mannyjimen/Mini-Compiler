#ifndef _INTERPRETER_
#define _INTERPRETER_

#include "Lox.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

#include <variant>
#include <vector>
#include <memory>
#include <stack>
#include <stdexcept>

class Environment;

//instead of try finally block in java, i can use C++ RAII to do the mutation of m_environment, and restore at destruction time
class StateGuard {
    public:
    StateGuard(std::shared_ptr<Environment>& managing, std::shared_ptr<Environment> newEnvironment): m_managing(managing), m_old(managing) {
        m_managing = newEnvironment;
    }
    ~StateGuard() {
        m_managing = m_old;
    }

    private:
    std::shared_ptr<Environment>& m_managing;
    std::shared_ptr<Environment> m_old;
};

struct LoxRuntimeError : public std::runtime_error{
    Token m_token;

    LoxRuntimeError(const Token& token, const std::string& message);
};

//POST-ORDER Traversal!
class Interpreter: public ExprVisitor, public StmtVisitor{
    public:

    Interpreter();
    void interpret(std::vector<std::shared_ptr<Stmt>> statements);

    private:

    std::shared_ptr<Environment> m_environment;
    
    std::stack<LoxObject> m_returns;
    bool isTruthy(const LoxObject& obj);
    bool isEqual(const LoxObject& a, const LoxObject& b);
    std::string stringify(const LoxObject& obj);

    LoxObject evaluate(std::shared_ptr<Expr> expr);
    void execute(std::shared_ptr<Stmt> stmt);

    //Expression interpreter implementations
    void visit(Literal& literal) override;
    void visit(Grouping& grouping) override;
    void visit(Unary& unary) override;
    void visit(Binary& binary) override;
    void visit(Variable& variable) override;
    void visit(Assign& assignExpr) override;

    //Statement interpreter implementations
    void visit(Expression& stmt) override;
    void visit(Print& stmt) override;
    void visit(Var& stmt) override;
    void visit(Block& stmt) override;
    void executeBlock(std::vector<std::shared_ptr<Stmt>> statements, std::shared_ptr<Environment> environment);
    void visit(IfStmt& stmt) override;

    void checkNumberOperand(const Token& op, const LoxObject& operand);
    void checkNumberOperands(const Token& op, const LoxObject& left, const LoxObject& right);
};

#endif