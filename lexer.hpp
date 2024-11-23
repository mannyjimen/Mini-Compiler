#ifndef LEXER_
#define LEXER_

//GOAL
//compile input source code file to a vector of tokens.
//for every line in the source code file, that is a separate vector. 

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

enum TokenClass{
    Number,
    Letter,
    OpenPara,
    ClosePara,
    Operation,
    Equal,
    Quote,
    Colon,
    Invalid,
};

struct Token{
    char m_token;
    TokenClass m_class;
    Token(const char& x){
        m_token = x;
        if (x >= 48 && x <= 57)
            m_class = Number;
        else if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
            m_class = Letter;
        else if (x == '+' || x == '-' || x == '*' || x == '/')
            m_class = Operation;
        else{
            switch(x){
                case '=':
                    m_class = Equal;
                    break;
                case '(':
                    m_class = OpenPara;
                    break;
                case ')':
                    m_class = ClosePara;
                    break;
                case '"':
                    m_class = Quote;
                    break;
                case ':':
                    m_class = Colon;
                    break;
                default: 
                    m_class = Invalid;
            }
        }
    }
};

class Lexer{
    public:
    Lexer(const std::string& src_file); //constructing Lexer with src file (text file with code)

    Token createToken(const char& x);
    std::vector<Token> getTokensForLine(const std::string& line); //return vector of tokens to be pushed to vector
    std::vector<std::vector<Token>> getAllTokens();
    void printTokens();

    private:
    std::vector<std::vector<Token>> linesOfTokens;  
};

#endif