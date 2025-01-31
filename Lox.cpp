#include "Lox.hpp"

Lox::Lox(int argc, char* argv[]){
    if (argc == 1){
        std::cout << "Running from prompt:\n";
        run_prompt();
    }
    else if (argc == 2){
        run_file(argv[0]);
        std::cout << "Running from input file:\n";
    }
    else{
        std::cout << "Error\n";
    }
}

void Lox::run_prompt(){
    return;
}

void Lox::run_file(std::string source_file){
    return;
}