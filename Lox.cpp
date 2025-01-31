#include "Lox.hpp"

Lox::Lox(int argc, char* argv[]){
    if (argc == 1){
        std::cout << "Running from prompt:\n";
        runPrompt();
    }
    else if (argc == 2){
        std::cout << "Running from input file:\n";
        runFile(argv[1]);
    }
    else{
        std::cout << "Error\n";
    }
}

void Lox::runPrompt(){
    std::string line;
    for (;;){ //infinite loop
        std::cout << "> "; 
        std::getline(std::cin, line);
        if (line.empty())
            break;
        run(line);
    }
}

void Lox::runFile(const std::string sourceFileName){
    std::string entireProg = "";
    std::string temp;
    
    std::ifstream sourceFile;
    sourceFile.open(sourceFileName);
    while (!sourceFile.eof()){
        std::getline(sourceFile, temp);
        entireProg += temp;
    }
    sourceFile.close();

    run(entireProg);
}

void Lox::run(const std::string source){
    std::cout << source << std::endl;
}