#include "Scanner.hpp"

Scanner::Scanner(std::string source){
    m_source = source;
    scanTokens();
}

std::vector<Token*> Scanner::scanTokens(){
    while (!isAtEnd()){
        //beginning of next lexeme
        m_start = m_current;
        scanToken();
    }
    //after we reach end of source we add EOF token
    //using 0 (since we dont care about the literal)
    m_tokens.push_back(new Token(TokenType::ENDOFFILE, "", 0, m_line));
    //printTokens();
    return m_tokens;
}

bool Scanner::isAtEnd(){
    return m_current >= m_source.size();
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
        //single char tokens that can possibly be double char tokens
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')){
                //we know its a comment, get to end of the line
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else{
                addToken(TokenType::SLASH);
            }
            break;
        //whitespace ignoring
        case ' ':
        case '\r':
        case '\t':
            break;

        //newline case
        case '\n':
            m_line++;
            break;

        //string
        case '"':
            string();
            break;
        
        default:
            //if encountered undefined single char Token
            Lox::error(m_line, "Unexpected character");
            break;
    }
}

char Scanner::advance(){
    return m_source[m_current++];
}

bool Scanner::match(char expected){
    if (isAtEnd())
        return false;
    if (m_source[m_current] != expected)
        return false;
    
    //will consume current character (since we know its part of lexeme)
    m_current++;
    return true;
}

char Scanner::peek(){
    if (isAtEnd())
        return '\0';
    return m_source[m_current];
}

void Scanner::string(){
    while(peek() != '"' && !isAtEnd()){
        //multiline string support
        if(peek() == '\n')
            m_line++;
        advance();
    }

    if(isAtEnd()){
        Lox::error(m_line, "Unterminated String.");
        return;
    }

    //we are at the closing " 
    advance();

    //adding the string minus the side " " quotes
    std::string value = m_source.substr(m_start + 1, m_current - m_start - 2);
    addToken(TokenType::STRING, value);
}

//using 0 as variant since we dont care in this case
void Scanner::addToken(TokenType type){
    addToken(type, 0);
}

//adding token with literal
void Scanner::addToken(TokenType type, std::variant<bool, int, std::string> literal){
    //retrieving lexeme
    std::string text = m_source.substr(m_start, m_current - m_start);
    //pushing new token to token vector
    m_tokens.push_back(new Token(type, text, literal , m_line));
}

void Scanner::printTokens(){
    for (auto it: m_tokens){
        std::cout << "Token Type: " << it->getTypeString() << " |";
        std::cout << " Literal: " << it->getLiteralString() << " |";
        std::cout << " Lexeme: " << it->getLexeme() << std::endl;
    }
}