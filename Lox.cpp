#include "Lox.hpp"

Lox::Lox(){
    std::cout << "Running from prompt\n";
}

Lox::Lox(std::string decider){
    std::cout << "Running from file\n";
}