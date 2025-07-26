#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include "Token.hpp"
#include "Interpreter.hpp"

#include <string>
#include <variant>
#include <unordered_map>

class Environment{
    public:
    Environment();
    void define(const std::string& name, const LoxObject& value);
    LoxObject get(const Token& name);
    private:
    std::unordered_map<std::string, LoxObject> values;

};

#endif
