#ifndef _INTERPRETER_
#define _INTERPRETER_

#include "ExpressionTypes.hpp"
#include "Lox.hpp"

#include <variant>
#include <memory>
#include <stack>
#include <stdexcept>

struct LoxRuntimeError : public std::runtime_error{
    Token m_token;

    LoxRuntimeError(const Token& token, const std::string& message);
};

//POST-ORDER Traversal!
class Interpreter: public Visitor{
    public:
    void interpret(std::shared_ptr<Expr> expr);

    private:
    std::stack<LoxObject> m_returns;
    bool isTruthy(const LoxObject& obj);
    bool isEqual(const LoxObject& a, const LoxObject& b);
    std::string stringify(const LoxObject& obj);

    LoxObject evaluate(std::shared_ptr<Expr> expr);

    void visit(Literal& literal) override;
    void visit(Grouping& grouping) override;
    void visit(Unary& unary) override;
    void visit(Binary& binary) override;

    void checkNumberOperand(const Token& op, const LoxObject& operand);
    void checkNumberOperands(const Token& op, const LoxObject& left, const LoxObject& right);
};

#endif