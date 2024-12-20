#ifndef LEXER_
#define LEXER_

//GOAL
// create function that takes input source file, turns that into string, then runs lexer constructor on it.
//

#include <vector>
#include <iostream>
#include <string>

//token classes (will probably add or delete some classes)
enum class TokenClass{
    Number,
    Letter,
    OpenPara,
    ClosePara,
    Operation,
    Equal,
    Quote,
    Colon,
    Invalid,
    EndOfLine,
};

struct Token{
    char m_char;
    TokenClass m_class;
    //constructs token for given character
    Token(const char& TokChar, const TokenClass TokClass): 
    m_char{TokChar}, m_class{TokClass} {}
};

class Lexer{
    public:
    Lexer(const std::string& entireProgram);
    //returns TokenClass of input char
    TokenClass decideClass(const char& TokChar);
    //helper function to create token for the given char parameter
    Token createToken(const char& x);
    //prints tokens in an organized manner (specifying character and token type)
    void printTokens();

    
    //getter function for parser. just returns entireTokenProgram
    std::vector<Token> getAllTokens();

    private:
    std::vector<Token> entireTokenProgram;  
};

#endif