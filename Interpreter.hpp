#ifndef _INTERPRETER_
#define _INTERPRETER_

#include "Expression.hpp"
#include "Statement.hpp"
#include "Environment.hpp"
#include "Lox.hpp"

#include <variant>
#include <vector>
#include <memory>
#include <stack>
#include <stdexcept>

class Environment;

struct LoxRuntimeError : public std::runtime_error{
    Token m_token;

    LoxRuntimeError(const Token& token, const std::string& message);
};

//POST-ORDER Traversal!
class Interpreter: public ExprVisitor, public StmtVisitor{
    public:

    void interpret(std::vector<std::shared_ptr<Stmt>> statements);
    Interpreter();

    private:

    Environment environment;
    
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

    //Statement interpreter implementations
    void visit(Expression& stmt) override;
    void visit(Print& stmt) override;
    void visit(Var& var) override;

    void checkNumberOperand(const Token& op, const LoxObject& operand);
    void checkNumberOperands(const Token& op, const LoxObject& left, const LoxObject& right);
};

#endif