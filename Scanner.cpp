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

bool Scanner::isAtEnd(){
    return m_current >= m_source.length();
}

void Scanner::scanToken(){
    char c = advance();
    switch (c){
        //single char tokens
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        default:
            //if encountered undefined single char Token
            Lox::error(m_line, "Unexpected character.");
            break;
    }
}

char Scanner::advance(){
    
}