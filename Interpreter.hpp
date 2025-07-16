#ifndef _INTERPRETER_
#define _INTERPRETER_

#include "ExpressionTypes.hpp"
#include <variant>
#include <memory>
#include <stack>

//POST-ORDER Traversal!

class Interpreter: public Visitor{
    public:
    std::stack<LoxObject> m_returns;
    bool isTruthy(const LoxObject& obj);
    bool isEqual(const LoxObject& a, const LoxObject& b, bool areBools, bool areDoubles, bool areStrings);

    LoxObject evaluate(std::shared_ptr<Expr> expr);

    void visit(Literal& literal) override;
    void visit(Grouping& grouping) override;
    void visit(Unary& unary) override;
    void visit(Binary& binary) override;
};

#endif