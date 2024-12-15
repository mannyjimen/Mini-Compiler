#ifndef LEXER_
#define LEXER_

//GOAL
//compile input source code file to a vector of tokens.
//for every line in the source code file, that is a separate vector.

//subgoal - use enum class instead of plain enums DONE
//- take input string instead of source file (can then create anotherfunction to take a string of a file)
//- make the lexer determine what type of token it is, not the token constructor DONE


//example:
//Source code//
//Y = 5
//Machine code (Vector of Tokens Only)//
//TokenVector = {Tok01, Tok02, Tok03, Tok04, Tok05}
//Tok01 has TokenClass Letter, char 'Y'
//Tok02 has TokenClass Space, char ' '
//Tok03 has TokenClass Equal, char '='
//Tok04 has TokenClass Space, char ' '
//Tok05 has TokenClass Number, char'5'

//thoughts
/*
number of vectors = number of lines in source code
Successfully adds all tokens to vectors, and vectors to lexer data member. 
Ready to begin parsing (I think lol)
*/

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
     //constructing Lexer with src file (text file with code)
    Lexer(const std::string& entireProgram);
    //returns TokenClass of input char
    TokenClass decideClass(const char& TokChar);
    //helper function to create token for the given char parameter
    Token createToken(const char& x);
    //return vector of tokens for specific line input
    std::vector<Token> getTokensForLine(const std::string& line);
    //returns linesOfTokens (vector of vectors of tokens)
    std::vector<std::vector<Token>> getAllTokens();
    //prints tokens in an organized manner (specifying character and token type)
    void printTokens();

    private:
    std::vector<std::vector<Token>> linesOfTokens;  
};

#endif