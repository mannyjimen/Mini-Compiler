#include "Environment.hpp"

void Environment::define(const std::string& name, const LoxObject& value){
    values.insert({name, value});
}

void Environment::assign(const Token& token, const LoxObject& value){
    if (values.count(token.m_lexeme)){
        values.at(token.m_lexeme) = value;
        return;
    }
    throw LoxRuntimeError(token, "Undefined variable '" + token.m_lexeme + "'.");
}

LoxObject Environment::get(const Token& name){
    if (values.count(name.m_lexeme)) return values.at(name.m_lexeme);
    throw LoxRuntimeError(name, "Undefined variable '" + name.m_lexeme + "'.");
}