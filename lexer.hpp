#ifndef LEXER_
#define LEXER_

//GOAL
//compile input source code to machine code that
//parser will understand. A single Vector of Tokens. 

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

/*maybe instead of having a single vector with a token that represents a new line
, a vector of vectors could be better, where each vector represents a new line
, could make code easier to read
number of vectors = number of lines in source code
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
    OpenQuote,
    CloseQuote,
    Colon,
    NextLine,
    Space,
};

class Token{
    public:
    

    private:
    char m_token;
    TokenClass m_class;
};

class Lexer{
    public:

    private:

    
};

#endif