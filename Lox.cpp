#include "Lox.hpp"

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

void Lox::runFile(const std::string& sourceFileName){
    std::string currentLine;
    std::string entireProg = "";

    std::ifstream sourceFile;
    //FIX
    //still have to implement error if file not found
    sourceFile.open(sourceFileName);
    //line by line, but sticking entire prog into one string, separated by '\n'
    while (!sourceFile.eof()){
        std::getline(sourceFile, currentLine);
        entireProg = entireProg + currentLine + '\n'; 
    }
    run(entireProg);

    sourceFile.close();
}

void Lox::run(const std::string& source){
    Scanner main(source);
    //check if theres error in code
    if (hadError){
        return;
    }
    //we are going to execute !!!
}

void Lox::error(int lineNum, const std::string& errorMessage){
    report(lineNum, "", errorMessage);
}

void Lox::error(Token token, const std::string& errorMessage){
    if (token.m_type == TokenType::ENDOFFILE){
        report(token.m_line, "at end", errorMessage);
    }
    else {
        report(token.m_line, " at '" + token.m_lexeme + "'", errorMessage);
    }
}

void Lox::report(int lineNum, const std::string& where, const std::string& message){
    std::cerr << "[line " << lineNum << "]" << " Error" << where << ": " << message << std::endl;
    hadError = true;
}