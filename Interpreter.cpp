#include "Interpreter.hpp"

void Interpreter::visit(Literal& literal){
    m_returns.push(literal.m_lit);
}

void Interpreter::visit(Grouping& grouping){
    evaluate(grouping.m_contents);
}

void Interpreter::visit(Unary& unary){
    LoxObject right = evaluate(unary.m_operand);

    switch (unary.m_logicalop.m_type){
        case TokenType::MINUS : 
            m_returns.push(-(std::get<double>(right)));
            return;
        case TokenType::BANG :
            m_returns.push(!isTruthy(right));
            return;
    }
    m_returns.push("NIL");
}

LoxObject Interpreter::evaluate(std::shared_ptr<Expr> expr){
    expr->accept(*this);
}

bool Interpreter::isTruthy(const LoxObject& obj){
    if (std::get_if<bool>(&obj)) return std::get<bool>(obj);
    else if (std::get_if<std::string>(&obj) && std::get<std::string>(obj) == "NIL") return false; 
    
    return true;
}

void Interpreter::visit(Binary& binary){
    LoxObject left = evaluate(binary.m_left);
    LoxObject right = evaluate(binary.m_right);
    //double dleft = std::get<double>(left); double dright = std::get<double>(right);
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

    switch (binary.m_op.m_type){
        case TokenType::MINUS:
            m_returns.push(d_left - d_right); return;
        case TokenType::SLASH:
            m_returns.push(d_left / d_right); return;
        case TokenType::STAR:
            m_returns.push(d_left * d_right); return;
        case TokenType::PLUS:
            if (areStrings){
                m_returns.push(s_left + s_right); return;
            }
            if (areDoubles){
                m_returns.push(d_left + d_right); return;
            }
            break;
        case TokenType::GREATER:
            m_returns.push(d_left > d_right); return;
        case TokenType::GREATER_EQUAL:
            m_returns.push(d_left >= d_right); return;
        case TokenType::LESS:
            m_returns.push(d_left < d_right); return;
        case TokenType::LESS_EQUAL:
            m_returns.push(d_left <= d_right); return;
        case TokenType::EQUAL_EQUAL:
            m_returns.push(isEqual(left, right, areBools, areDoubles, areStrings)); return;
        case TokenType::BANG_EQUAL:
            m_returns.push(!isEqual(left, right, areBools, areDoubles, areStrings)); return;
    }
    m_returns.push("NIL"); return;
} 

bool Interpreter::isEqual(const LoxObject& a, const LoxObject& b, bool areBools, bool areDoubles, bool areStrings){
    if (areBools || areDoubles){
        return a == b;
    }
    if (areStrings){
        if (std::get<std::string>(a) == "NIL" && std::get<std::string>(b) == "NIL") return true;
    }
    return false;
}