#include "Scanner.hpp"

Scanner::Scanner(std::string source){
    this->m_source = source;
}

std::vector<Token*> Scanner::scanTokens(){
    while (!isAtEnd){
        //beginning of next lexeme
        m_start = m_current;
        scanToken();
    }
    //after we reach end of source we add EOF token
    //not sure if nullptr will work here
    m_tokens.push_back(new Token(TokenType::ENDOFFILE, "", nullptr, m_line));
    return m_tokens;
}

void Scanner::scanToken(){
    char c = advance();
}

bool Scanner::isAtEnd(){
    return m_current >= m_source.length();
}

char Scanner::advance(){
    
}