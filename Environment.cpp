#include "Environment.hpp"

Environment::Environment(){
    
}

void Environment::define(const std::string& name, const LoxObject& value){
    values.insert({name, value});
}

LoxObject Environment::get(const Token& name){
    if (values.count(name.m_lexeme)) return values.at(name.m_lexeme);
    throw LoxRuntimeError(name, "Undefined variable " + name.m_lexeme + ".");
}