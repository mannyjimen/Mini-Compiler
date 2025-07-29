#include "Environment.hpp"

void Environment::define(const std::string& name, const LoxObject& value){
    std::cout << "about to call define\n";
    values.insert({name, value});
    std::cout << "just called define\n";
}

LoxObject Environment::get(const Token& name){
    if (values.count(name.m_lexeme)) return values.at(name.m_lexeme);
    throw LoxRuntimeError(name, "Undefined variable " + name.m_lexeme + ".");
}