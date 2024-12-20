#include "lexer.hpp"
#include <fstream>


//writes entire string program into member vector
Lexer::Lexer(const std::string& stringedProgram){
    for (char c: stringedProgram){
        entireTokenProgram.push_back(createToken(c));
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
            case ';':
                return TokenClass::EndOfLine;
            default: 
                return TokenClass::Invalid;
        }
    }
}

Token Lexer::createToken(const char& x){
    Token newTok(x, decideClass(x));
    return newTok;
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
        case(TokenClass::EndOfLine):
            output << "EndOfLine";
            break;
    } 
    return output;
}

void Lexer::printTokens(){
    for (Token currentToken: entireTokenProgram)
        std::cout << currentToken << '\n';
}

std::vector<Token> Lexer::getAllTokens(){
    return entireTokenProgram; 
}