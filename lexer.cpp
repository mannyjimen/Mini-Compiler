#include "lexer.hpp"
#include <fstream>


//writes entire string program into member vector
Lexer::Lexer(const std::string& source_text){
    
}

TokenClass Lexer::decideClass(const std::string token_string){
    // if (TokChar >= 48 && TokChar <= 57)
    //     return TokenClass::Number;
    // else if ((TokChar >= 65 && TokChar <= 90) || (TokChar >= 97 && TokChar <= 122))
    //     return TokenClass::Letter;
    // else if (TokChar == '+' || TokChar == '-' || TokChar == '*' || TokChar == '/')
    //     return TokenClass::Operation;
    // else{
    //     switch(TokChar){
    //         case '=':
    //             return TokenClass::Equal;
    //             break;
    //         case '(':
    //             return TokenClass::OpenPara;
    //             break;
    //         case ')':
    //             return TokenClass::ClosePara;
    //             break;
    //         case '"':
    //             return TokenClass::Quote;
    //             break;
    //         case ':':
    //             return TokenClass::Colon;
    //             break;
    //         case ';':
    //             return TokenClass::EndOfLine;
    //             break;
    //         case ' ':
    //             return TokenClass::Space;
    //         default: 
    //             return TokenClass::Invalid;
    //     }
    // }
    return TokenClass::Invalid;
}

Token Lexer::createToken(const std::string x){
    Token newTok(x, decideClass(x));
    return newTok;
}

//operator overload << for Token objects, helper to printTokens
std::ostream& operator<<(std::ostream& output, Token& rhs){
    output << "Char: " << rhs.m_name << " | Tokenclass: ";
    switch(rhs.m_class){
        case(TokenClass::Number):
            output << "Number";
            break;
        case(TokenClass::Letter):
            output << "Letter";
            break; 
        case(TokenClass::OpenParen):
            output << "OpenParen";
            break; 
        case(TokenClass::CloseParen):
            output << "CloseParen";
            break; 
        case(TokenClass::Operator):
            output << "Operator";
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
        case(TokenClass::Space):
            output << "Space";
            break;
    } 
    return output;
}

void Lexer::printTokens(){
    for (Token curr_token: m_tokenized_program)
        std::cout << curr_token << '\n';
}

std::vector<Token> Lexer::getTokens() const{
    return this->m_tokenized_program; 
}