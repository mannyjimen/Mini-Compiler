#include "Interpreter.hpp"

LoxRuntimeError::LoxRuntimeError(const Token& token, const std::string& message)
    : std::runtime_error(message), m_token(token) {}

    
//Interpreter function implementations

void Interpreter::interpret(std::vector<std::shared_ptr<Stmt>> statements){
    try{
        for (std::shared_ptr<Stmt> stmt : statements)
            execute(stmt);
    } catch (LoxRuntimeError error){
        Lox::runtimeError(error);
    }
}

//FIX
//this is where I need to return (use stack) a value
LoxObject Interpreter::evaluate(std::shared_ptr<Expr> expr){
    expr->accept(*this);
    LoxObject ret = m_returns.top();
    m_returns.pop();
    return ret;
}

void Interpreter::execute(std::shared_ptr<Stmt> stmt){
    stmt->accept(*this);
}

void Interpreter::visit(Literal& literal){
    m_returns.push(literal.m_lit);
}

void Interpreter::visit(Unary& unary){
    LoxObject right = evaluate(unary.m_operand);

    switch (unary.m_logicalop.m_type){
        case TokenType::MINUS : 
            checkNumberOperand(unary.m_logicalop, right);
            m_returns.push(-(std::get<double>(right)));
            return;
        case TokenType::BANG :
            m_returns.push(!isTruthy(right));
            return;
    }
    std::monostate nullObj;
    m_returns.push(nullObj);
}

void Interpreter::visit(Grouping& grouping){
    m_returns.push(evaluate(grouping.m_contents));
}

void Interpreter::visit(Binary& binary){
    LoxObject left = evaluate(binary.m_left);
    LoxObject right = evaluate(binary.m_right);
    bool areBools = false;
    bool areDoubles = false;
    bool areStrings = false;
    bool b_left, b_right;
    double d_left, d_right;
    std::string s_left, s_right;
    if (std::get_if<bool>(&left) && std::get_if<bool>(&right)) areBools = true;
    if (std::get_if<double>(&left) && std::get_if<double>(&right)) areDoubles = true;
    if (std::get_if<std::string>(&left) && std::get_if<std::string>(&right)) areStrings = true;
    if(areBools){
        b_left = std::get<bool>(left); b_right = std::get<bool>(right);
    }
    else if(areDoubles){
        d_left = std::get<double>(left); d_right = std::get<double>(right);
    }
    else if (areStrings){
        s_left = std::get<std::string>(left); s_right = std::get<std::string>(right);
    }

    //FIX
    //if adding strings, error will occur if operator other than + is used
    switch (binary.m_op.m_type){
        case TokenType::MINUS:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left - d_right); return;
        case TokenType::SLASH:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left / d_right); return;
        case TokenType::STAR:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left * d_right); return;
        case TokenType::PLUS:
            if (areStrings){
                m_returns.push(s_left + s_right); return;
            }
            if (areDoubles){
                m_returns.push(d_left + d_right); return;
            }
            throw LoxRuntimeError(binary.m_op, "Operands must be both numbers or both strings.");
        case TokenType::GREATER:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left > d_right); return;
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left >= d_right); return;
        case TokenType::LESS:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left < d_right); return;
        case TokenType::LESS_EQUAL:
            checkNumberOperands(binary.m_op, left, right);
            m_returns.push(d_left <= d_right); return;
        case TokenType::EQUAL_EQUAL:
            m_returns.push(isEqual(left, right)); return;
        case TokenType::BANG_EQUAL:
            m_returns.push(!isEqual(left, right)); return;
    }
    std::monostate nullObj;
    m_returns.push(nullObj); return;
} 

//Statement Implementation Functions
void Interpreter::visit(Expression& stmt){
    evaluate(stmt.m_expr);
}

void Interpreter::visit(Print& stmt){
    LoxObject value = evaluate(stmt.m_expr);
    std::cout << stringify(value) << std::endl;
}

//helper funcs

std::string Interpreter::stringify(const LoxObject& obj){
    if (std::get_if<std::monostate>(&obj)) return "nil";
    else if (std::get_if<bool>(&obj)){
        switch (std::get<bool>(obj)){
            case true:
                return "true";
            default:
                return "false";
        }
    }
    else if (std::get_if<double>(&obj)){
        std::string sdouble = std::to_string(std::get<double>(obj));
        int r = sdouble.size() - 1;
        while (sdouble[r] == '0') r--;
        if (sdouble[r] == '.') r--;
        sdouble = sdouble.substr(0, r + 1);
        return sdouble;
        //FIX
        //remove trailing zeros from double.
    }
    return std::get<std::string>(obj);
}

bool Interpreter::isTruthy(const LoxObject& obj){
    if (std::get_if<bool>(&obj)) return std::get<bool>(obj);
    else if (std::get_if<std::monostate>(&obj)) return false; 
    return true;
} 

bool Interpreter::isEqual(const LoxObject& a, const LoxObject& b){
    if (std::get_if<std::monostate>(&a) && std::get_if<std::monostate>(&b)) return true;
    if (std::get_if<std::monostate>(&a)) return false;
    return a == b;
}

//checking for unexpected data type (unary minus op)
void Interpreter::checkNumberOperand(const Token& op, const LoxObject& operand){
    if (std::get_if<double>(&operand)) return;
    throw LoxRuntimeError(op, "Operand must be a number.");
}

//checking for unexpected data type (binary, excluding '+')
void Interpreter::checkNumberOperands(const Token& op, const LoxObject& left, const LoxObject& right){
    if (std::get_if<double>(&left) && std::get_if<double>(&right)) return;
    throw LoxRuntimeError(op, "Operands must both be numbers.");
}