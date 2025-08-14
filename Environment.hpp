#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include "Token.hpp"
#include "Interpreter.hpp"

#include <string>
#include <variant>
#include <unordered_map>

class Environment{
    public:
    //global scope environment constructor
    Environment();
    //local scope environment constructor, enclosing is the immediate surrounding scope's environment.
    // Environment(std::shared_ptr<Environment> enclosing);
    Environment(std::shared_ptr<Environment> enclosing);

    std::shared_ptr<Environment> m_enclosing;


    void define(const std::string& name, const LoxObject& value);
    void assign(const Token& token, const LoxObject& value);
    LoxObject get(const Token& name);
    private:
    std::unordered_map<std::string, LoxObject> values;

};

#endif
