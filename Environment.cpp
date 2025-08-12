#include "Environment.hpp"

Environment::Environment(){
    m_enclosing = nullptr;
}

Environment::Environment(std::shared_ptr<Environment> enclosing){
    m_enclosing = enclosing;
}

void Environment::define(const std::string& name, const LoxObject& value){
    values.insert({name, value});
}

void Environment::assign(const Token& token, const LoxObject& value){
    if (values.count(token.m_lexeme)){
        values.at(token.m_lexeme) = value;
        return;
    }

    if (m_enclosing != nullptr) {
        m_enclosing->assign(token, value);
        return;
    }

    throw LoxRuntimeError(token, "Undefined variable '" + token.m_lexeme + "'.");
}

LoxObject Environment::get(const Token& name){
    if (values.count(name.m_lexeme)) return values.at(name.m_lexeme);

    if (m_enclosing != nullptr) return m_enclosing->get(name);

    throw LoxRuntimeError(name, "Undefined variable '" + name.m_lexeme + "'.");
}