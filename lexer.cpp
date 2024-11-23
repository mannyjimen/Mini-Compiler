#include "lexer.hpp"
#include <fstream>

Lexer::Lexer(const std::string& src_file){
    std::ifstream srcFile("example_code.txt"); //creates srcFile ifstream 
    std::string currentLine;
    while (getline(srcFile, currentLine)){ //reads lines of srcFile one by one
        //gets vector of tokens for each line, pushes to back of linesOfTokens
        linesOfTokens.push_back(getTokensForLine(currentLine)); 
    }
}

Token Lexer::createToken(const char& x){
    Token newTok(x);
    return newTok;
}

std::vector<Token> Lexer::getTokensForLine(const std::string& line){
    std::vector<Token> finalVec;
    for (int currentIndex = 0; currentIndex < line.size(); currentIndex++){
        if (line[currentIndex] != ' ') //if current char is not a space
            finalVec.push_back(createToken(line[currentIndex]));
    }
    return finalVec;
}

std::vector<std::vector<Token>> Lexer::getAllTokens(){
    return linesOfTokens;
}

//operator overload << for Token objects, helper to printTokens
std::ostream& operator<<(std::ostream& output, Token& rhs){
    output << "Char: " << rhs.m_token << " | Tokenclass: ";
    switch(rhs.m_class){
        case(0):
            output << "Number";
            break;
        case(1):
            output << "Letter";
            break; 
        case(2):
            output << "OpenPara";
            break; 
        case(3):
            output << "ClosePara";
            break; 
        case(4):
            output << "Operation";
            break; 
        case(5):
            output << "Equal";
            break; 
        case(6):
            output << "Quote";
            break;
        case(7):
            output << "Colon";
            break;
        case(8):
            output << "Invalid";
            break;  
    } 
    return output;
}

void Lexer::printTokens(){
    std::vector<Token> currentLineTokens;
    int currLine = 0;
    for (auto currLineIt : linesOfTokens){
        currLine++;
        std::cout << "Line " << currLine << " ~\n";
        currentLineTokens = currLineIt;
        for (auto currTokIt : currentLineTokens){
            std::cout << currTokIt << "\n";
        }
    }
}

