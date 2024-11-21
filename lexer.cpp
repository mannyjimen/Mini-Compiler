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

Token Lexer::createToken(const char& x){ //token creation helper function
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

void Lexer::printTokens(){

}

