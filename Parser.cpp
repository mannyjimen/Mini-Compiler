#include "Parser.hpp"
/*CONSTRUCTION OF TREE. Making sure grammar is good, and constructing
AST out of all these tokens!*/

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens){
    m_tokens = tokens;
}

std::vector<std::shared_ptr<Stmt>> Parser::parse(){    
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!isAtEnd()){
        statements.push_back(declaration());
    }
    return statements;
}

bool Parser::match(const std::vector<TokenType> types){
    for (const TokenType& type: types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(const TokenType& type, const std::string& message){
    if(check(type)) return advance();
    //throwing ParseError, will be caught in parse()
    throw error(peek(), message);
}

Token Parser::advance(){
    if (!isAtEnd()) m_current++;
    return previous();
}

bool Parser::check(TokenType type) const{
    if (isAtEnd()) return false;
    return peek().m_type == type;
}

Token Parser::peek() const{
    return *m_tokens[m_current];
}

Token Parser::previous() const{
    return *m_tokens[m_current - 1];
}

bool Parser::isAtEnd() const{
    return peek().m_type == TokenType::ENDOFFILE;
}

//Expression parsing implementations
std::shared_ptr<Expr> Parser::expression(){
    return assignment();
}

std::shared_ptr<Expr> Parser::assignment(){
    //assignment -> IDENTIFIER '=' assignment | equality
    std::shared_ptr<Expr> expr = logical_or();

    if (match({TokenType::EQUAL})){
        Token equals = previous();
        std::shared_ptr<Expr> value = assignment();
        
        //downcasting shared_ptr<Expr> to shared_ptr<Variable> without creating extra shared_ptr (dynamic_pointer_cast)
        if (std::shared_ptr<Variable> tempVariable = std::dynamic_pointer_cast<Variable>(expr)){
            Token new_tokenName = tempVariable->m_tokenName;
            std::shared_ptr<Assign> assignReturn(new Assign(new_tokenName, value));
            return std::make_shared<Assign>(tempVariable->m_tokenName, value);
        }
        error(equals, "Invalid assignment target.");
    }
    //this is not an assignment
    return expr;
}

std::shared_ptr<Expr> Parser::logical_or() {
    std::shared_ptr<Expr> expr = logical_and();

    while (match({TokenType::OR})) {
        Token logical_op = previous();
        std::shared_ptr<Expr> right_expr = logical_and();
        expr = std::make_shared<Logical>(expr, logical_op, right_expr);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::logical_and() {
    std::shared_ptr<Expr> expr = equality();

    while (match({TokenType::AND})) {
        Token logical_op = previous();
        std::shared_ptr<Expr> right_expr = equality();
        expr = std::make_shared<Logical>(expr, logical_op, right_expr);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::equality(){
    //equality -> comparison( ("!=" | "==") comparison )*
    //comparison...
    std::shared_ptr<Expr> expr = comparison();

    //...(("!="|"==")comparison)*
    while(match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})){
        Token op = previous();
        std::shared_ptr<Expr> right = comparison(); //parsing the next (...)*
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right)); //appending to expr
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison(){
    //comparison -> term( ( ">" | ">=" | "<" | "<=") term )*
    std::shared_ptr<Expr> expr = term();

    while(match({TokenType::LESS, TokenType::LESS_EQUAL
        ,TokenType::GREATER, TokenType::GREATER_EQUAL})){
        Token op = previous();            
        std::shared_ptr<Expr> right = term();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term(){
    std::shared_ptr<Expr> expr = factor();

    while(match({TokenType::PLUS, TokenType::MINUS})){
        Token op = previous();            
        std::shared_ptr<Expr> right = factor();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor(){
    std::shared_ptr<Expr> expr = unary();

    while(match({TokenType::STAR, TokenType::SLASH})){
        Token op = previous();            
        std::shared_ptr<Expr> right = unary();
        expr = std::shared_ptr<Binary>(new Binary(expr, op, right));
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary(){
    //unary -> ("!"|"-") unary | primary
    if (match({TokenType::MINUS, TokenType::BANG})){
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::shared_ptr<Unary>(new Unary(op, right));
    }
    return primary();
}

std::shared_ptr<Expr> Parser::primary(){
    if (match({TokenType::FALSE})) return std::shared_ptr<Literal>(new Literal(false));
    if (match({TokenType::TRUE})) return std::shared_ptr<Literal>(new Literal(true));
    //FIX DONE: Might have to rework how null/nil works
    std::monostate nullObj;
    if (match({TokenType::NIL})) return std::shared_ptr<Literal>(new Literal(nullObj));
    if (match({TokenType::NUMBER, TokenType::STRING})){
        return std::shared_ptr<Literal>(new Literal(previous().m_literal));
    }

    if (match({TokenType::IDENTIFIER})) return std::shared_ptr<Variable>(new Variable(previous()));
    //grouping case 
    if (match({TokenType::LEFT_PAREN})){
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::shared_ptr<Grouping>(new Grouping(expr));
    }

    throw error(peek(), "Expect expression.");
}

//Statement parsing implementations

//error recovery is here (catching ParseError for synchronization)
std::shared_ptr<Stmt> Parser::declaration(){
    try{
        if (match({TokenType::VAR})) return declVar();
        return statement();
    } catch(ParseError error){
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<Stmt> Parser::declVar(){
    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");

    std::shared_ptr<Expr> initExpr = nullptr;
    if (match({TokenType::EQUAL})){
        initExpr = expression();
    }
    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");
    return std::shared_ptr<Var>(new Var(name, initExpr));
}

std::shared_ptr<Stmt> Parser::statement(){
    if (match({TokenType::IF})) return ifStatement();
    if (match({TokenType::PRINT})) return printStatement();
    if (match({TokenType::WHILE})) return whileStatement();
    if (match({TokenType::FOR})) return forStatement();
    if (match({TokenType::LEFT_BRACE})){
        return std::make_shared<Block>(Block(block()));
    }
    return expressionStatement();
}

std::shared_ptr<Stmt> Parser::expressionStatement(){
    std::shared_ptr<Expr> expr = expression();
    consume(TokenType::SEMICOLON, "Expected a ';' after expression.");
    return std::make_shared<Expression>(expr);
}

std::shared_ptr<Stmt> Parser::printStatement(){
    //we matched and consumed Print token already.
    std::shared_ptr<Expr> value = expression();
    consume(TokenType::SEMICOLON, "Expected a ';' after value");
    return std::make_shared<Print>(value);
}

std::vector<std::shared_ptr<Stmt>> Parser::block(){
    std::vector<std::shared_ptr<Stmt>> allBlockStatements;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        allBlockStatements.push_back(declaration());
    }

    consume(TokenType::RIGHT_BRACE, "Expected a '}' after block.");
    return allBlockStatements;
}

std::shared_ptr<Stmt> Parser::ifStatement() {
    consume(TokenType::LEFT_PAREN, "Expected a '(' after 'if'.");

    std::shared_ptr<Expr> conditional = expression();

    consume(TokenType::RIGHT_PAREN, "Expected a ')' after conditional.");
    
    std::shared_ptr<Stmt> thenBranch = statement();
    std::shared_ptr<Stmt> elseBranch = nullptr;

    if (match({TokenType::ELSE})) {
        elseBranch = statement();
    }

    return std::make_shared<IfStmt>(conditional, thenBranch, elseBranch);
}

std::shared_ptr<Stmt> Parser::whileStatement() {
    consume(TokenType::LEFT_PAREN, "Expected a '(' after 'while'.");
    std::shared_ptr<Expr> condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expect a ')' after 'while' condition.");
    std::shared_ptr<Stmt> body = statement(); //not allowing declVar non-blocked

    return std::make_shared<While>(condition, body);
}

std::shared_ptr<Block> desugarForLoop(std::shared_ptr<Stmt> initializer, std::shared_ptr<Expr> condition, std::shared_ptr<Expr> increment, std::shared_ptr<Stmt> body) {
    std::shared_ptr<Expression> incrementExpr = nullptr;
    if (increment != nullptr) {
        incrementExpr = std::make_shared<Expression>(increment);
    } 
    
    //creating contents of while loop
    std::vector<std::shared_ptr<Stmt>> whileContents;
    if (increment == nullptr) {
        whileContents = {body};
    } else {
        whileContents = {body, incrementExpr};
    }

    std::shared_ptr<Block> whileLoopStatement = std::make_shared<Block>(whileContents);

    //creating while loop
    if (condition == nullptr) { //no condition? infinite loop
        condition = std::make_shared<Literal>(true); //true for condition
    }
    std::shared_ptr<While> forLoopToWhileLoop = std::make_shared<While>(condition, whileLoopStatement);

    //creating block that contains for loop to while loop, starting with initializer statement
    std::vector<std::shared_ptr<Stmt>> allContents;
    if (initializer == nullptr) {
        allContents = {forLoopToWhileLoop};
    } else {
        allContents = {initializer, forLoopToWhileLoop};
    }
    std::shared_ptr<Block> forLoopBlock = std::make_shared<Block>(allContents);

    return forLoopBlock;
}

std::shared_ptr<Stmt> Parser::forStatement() {
    consume(TokenType::LEFT_PAREN, "Expected a '(' after 'for'.");
    std::shared_ptr<Stmt> initializer;
    if (match({TokenType::SEMICOLON})) { //no statement 
        initializer = nullptr;
    } else if (match({TokenType::VAR})){
        initializer = declVar();
    } else {
        initializer = expressionStatement();
    }

    std::shared_ptr<Expr> condition = nullptr;
    if (!check(TokenType::SEMICOLON)) {
        condition = expression();
    }

    consume(TokenType::SEMICOLON, "Expected a ';' after for loop condition.");
    
    std::shared_ptr<Expr> increment = nullptr;
    if (!check(TokenType::RIGHT_PAREN)) {
        increment = expression();
    }
    consume(TokenType::RIGHT_PAREN, "Expected a ')' after for loop increment");

    std::shared_ptr<Stmt> body = statement();

    //desugaring time
    //for loop is a while loop
    /*
        for (var x = 0; x < 10; x = x + 1) {
            //contents
        }
    
    is equal to
    {
        var x = 0;
        while (x < 10) {
            //contents
            x = x + 1;
        }
    }
        initializer goes on outside of block
        while loop gets condition
        statement for while loop is contents with increment

    */

    // std::shared_ptr<Expression> incrementExpr = nullptr;
    // if (increment != nullptr) {
    //     incrementExpr = std::make_shared<Expression>(increment);
    // }

    // //creating contents of while loop
    // std::vector<std::shared_ptr<Stmt>> whileContents;
    // if (increment == nullptr) {
    //     whileContents = {body};
    // } else {
    //     whileContents = {body, incrementExpr};
    // }

    // std::shared_ptr<Block> whileLoopStatement = std::make_shared<Block>(whileContents);

    // //creating while loop
    // if (condition == nullptr) { //no condition? infinite loop
    //     condition = std::make_shared<Literal>(true); //true for condition
    // }
    // std::shared_ptr<While> forLoopToWhileLoop = std::make_shared<While>(condition, whileLoopStatement);

    // //creating block that contains for loop to while loop, starting with initializer statement
    // std::vector<std::shared_ptr<Stmt>> allContents;
    // if (initializer == nullptr) {
    //     allContents = {forLoopToWhileLoop};
    // } else {
    //     allContents = {initializer, forLoopToWhileLoop};
    // }
    // std::shared_ptr<Block> forLoopBlock = std::make_shared<Block>(allContents);

    return desugarForLoop(initializer, condition, increment, body);
}

//Error function implementations

ParseError Parser::error(const Token& token, const std::string& message){
    Lox::error(token, message);
    ParseError signal; return signal;
}

void Parser::synchronize(){
    //currently at broken token, going to move forward once.
    advance();

    while(!isAtEnd()){
        //checking if we are at the start of a statement
        //PROBABLY starting a new statement (not guaranteed)
        if(previous().m_type == TokenType::SEMICOLON) return;
        switch(peek().m_type){
            case TokenType::RETURN:
            case TokenType::PRINT:
            case TokenType::FOR:
            case TokenType::WHILE:
            case TokenType::IF:
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
                return;
        }
        //discarding token
        advance();
    }
}