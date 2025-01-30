#include "Lox.hpp"

Lox::Lox(std::string decider){
    if (decider.empty()){
        std::cout << "Running prompt\n";
    }
    else{
        std::cout << "Reading from file\n";
    }
}