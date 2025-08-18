#include "Lox.hpp"
#include "Interpreter.hpp"

//interpreter definition (NEEDED)
Interpreter Lox::interpreter;

//defining and initializng m_repl flag
bool Lox::m_repl = false;


Lox::Lox(int argc, char* argv[]){
    //learn about exceptions throw catch
    if (argc > 2){
        error(-1, "Too many arguments when executing");
        return;
    }
    if (argc == 1){
        m_repl = true;
        runPrompt();
    }
    else {
        m_repl = false;
        runFile(argv[1]);
    }
}

void Lox::runPrompt(){
    std::string line;
    for (;;){ //infinite loop
        hadError = false;
        std::cout << "> "; 
        std::getline(std::cin, line);
        if (line.empty())
            break;
        run(line);
        
    }
}

void Lox::runFile(const std::string& sourceFileName){
    std::string currentLine;
    std::string entireProg = "";

    std::ifstream sourceFile;
    //FIX - still have to implement error if file not found
    sourceFile.open(sourceFileName);
    //line by line, but sticking entire prog into one string, separated by '\n'
    while (!sourceFile.eof()){
        std::getline(sourceFile, currentLine);
        entireProg = entireProg + currentLine + '\n'; 
    }
    run(entireProg);

    //Unix/POSIX Convention for exit codes (shell etiquette)

    //data format error
    if (hadError) std::exit(65);
    //internal software error
    if (hadRuntimeError) std::exit(70);
    sourceFile.close();
}

void Lox::run(const std::string& source){
    Scanner scanner(source);
    std::vector<std::shared_ptr<Token>> tokens = scanner.scanTokens();
    Parser parser(tokens);
    std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
    //check if theres error in code
    if (hadError){
        return;
    }
    // AstPrinter astprinter;
    // astprinter.print(expression);
    
    interpreter.interpret(statements);
    //we are going to execute !!!
}

void Lox::error(int lineNum, const std::string& errorMessage){
    report(lineNum, "", errorMessage);
}

void Lox::error(Token token, const std::string& errorMessage){
    if (token.m_type == TokenType::ENDOFFILE){
        report(token.m_line, " at end", errorMessage);
    }
    else {
        report(token.m_line, " at '" + token.m_lexeme + "'", errorMessage);
    }
}

void Lox::runtimeError(LoxRuntimeError error){
    std::cerr << error.what() << " [line " << error.m_token.m_line << "]\n";
    hadRuntimeError = true;
}

void Lox::report(int lineNum, const std::string& where, const std::string& message){
    std::cerr << "[line " << lineNum << "]" << " Error" << where << ": " << message << std::endl;
    hadError = true;
}

bool Lox::isREPL(){
    return m_repl;
}