#include "Lox.hpp"

Lox::Lox(int argc, char* argv[]){
    //learn about exceptions throw catch
    if (argc > 2){
        error(-1, "Too many arguments when executing");
    }
    if (argc == 1){
        runPrompt();
    }
    else {
        runFile(argv[1]);
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

        hadError = true; //if error in code, don't want interactive to stop
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
    //check if theres error in code

    if (hadError){
        return;
    }
}

void Lox::error(int lineNum, std::string errorMessage){
    report(lineNum, "", errorMessage);
}

void Lox::report(int lineNum, std::string where, std::string message){
    std::cerr << "[line " << lineNum << "]" << " Error" << where << ": " << message;
    hadError = true;
}