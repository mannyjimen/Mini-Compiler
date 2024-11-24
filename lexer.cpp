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

TokenClass Lexer::decideClass(const char& TokChar){
    if (TokChar >= 48 && TokChar <= 57)
        return TokenClass::Number;
    else if ((TokChar >= 65 && TokChar <= 90) || (TokChar >= 97 && TokChar <= 122))
        return TokenClass::Letter;
    else if (TokChar == '+' || TokChar == '-' || TokChar == '*' || TokChar == '/')
        return TokenClass::Operation;
    else{
        switch(TokChar){
            case '=':
                return TokenClass::Equal;
                break;
            case '(':
                return TokenClass::OpenPara;
                break;
            case ')':
                return TokenClass::ClosePara;
                break;
            case '"':
                return TokenClass::Quote;
                break;
            case ':':
                return TokenClass::Colon;
                break;
            default: 
                return TokenClass::Invalid;
        }
    }
}


Token Lexer::createToken(const char& x){
    Token newTok(x, decideClass(x));
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
    output << "Char: " << rhs.m_char << " | Tokenclass: ";
    switch(rhs.m_class){
        case(TokenClass::Number):
            output << "Number";
            break;
        case(TokenClass::Letter):
            output << "Letter";
            break; 
        case(TokenClass::OpenPara):
            output << "OpenPara";
            break; 
        case(TokenClass::ClosePara):
            output << "ClosePara";
            break; 
        case(TokenClass::Operation):
            output << "Operation";
            break; 
        case(TokenClass::Equal):
            output << "Equal";
            break; 
        case(TokenClass::Quote):
            output << "Quote";
            break;
        case(TokenClass::Colon):
            output << "Colon";
            break;
        case(TokenClass::Invalid):
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

