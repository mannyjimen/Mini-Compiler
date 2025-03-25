#include "Lox.hpp"
#include "Scanner.hpp"

Lox::Lox(int argc, char* argv[]){
    //learn about exceptions throw catch
    if (argc > 2){
        error(-1, "Too many arguments when executing");
        return;
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
    std::string currentLineSource;

    std::ifstream sourceFile;
    //still have to implement error if file not found
    sourceFile.open(sourceFileName);
    while (!sourceFile.eof()){
        std::getline(sourceFile, currentLineSource);
        run(currentLineSource);
    }
    sourceFile.close();
}

void Lox::run(const std::string source){
    Scanner main(source);
    //check if theres error in code
    if (hadError){
        return;
    }
    //we are going to execute !!!
}

void Lox::error(int lineNum, std::string errorMessage){
    report(lineNum, "", errorMessage);
}

void Lox::report(int lineNum, std::string where, std::string message){
    std::cerr << "[line " << lineNum << "]" << " Error" << where << ": " << message << std::endl;
    hadError = true;
}