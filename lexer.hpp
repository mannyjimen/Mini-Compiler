#ifndef LEXER_
#define LEXER_

//goal
//lexer is for converting source text -> tokens. 
//tokens could be multiple characters, or a single character

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
    Space,
    Invalid,
    EndOfLine,
};

struct Token{
    std::string m_name;
    TokenClass m_class;
    //constructs token for given character
    Token(const std::string token_name, const TokenClass token_class): 
    m_name{token_name}, m_class{token_class} {}
};

class Lexer{
    public:
    Lexer(const std::string& source_text);
    //returns TokenClass of input char
    TokenClass decideClass(const std::string token_string);
    //helper function to create token for the given char parameter
    Token createToken(const std::string x);

    //prints tokens in an organized manner (specifying character and token type)
    void printTokens();

    
    //getter function for parser. just returns entireTokenProgram
    std::vector<Token> getAllTokens() const;

    private:
    std::vector<Token> m_tokenized_program;  
};

#endif