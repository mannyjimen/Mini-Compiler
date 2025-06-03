#include "ExpressionTypes.hpp"

//constructors
Binary::Binary(Expr* left, Token op, Expr* right){
        m_left = left;
        m_op = op;
        m_right = right;
}

Literal::Literal(Token lit){
        m_lit = lit;
    }

Unary::Unary(Token logicalop, Expr* operand){
        m_logicalop = logicalop;
        m_operand = operand;
    }

Grouping::Grouping(Expr* contents){
        m_contents = contents;
    }

//accept implemenatations

void Binary::accept(Visitor& visitor){
    return visitor.visit(*this);
}
void Literal::accept(Visitor& visitor){
    return visitor.visit(*this);
}
void Unary::accept(Visitor& visitor){
    return visitor.visit(*this);
}
void Grouping::accept(Visitor& visitor){
    return visitor.visit(*this);
}
   
//AST Visitor Implementations
void AstVisitor::visit(Binary& binary){
    parenthesize(binary.m_op.getLexeme(), {binary.m_left, binary.m_right});
}

void AstVisitor::visit(Unary& unary){
    parenthesize(unary.m_logicalop.getLexeme(), {unary.m_operand});
}

void AstVisitor::visit(Grouping& grouping){
   parenthesize("group", {grouping.m_contents});
}

//base case recursion
void AstVisitor::visit(Literal& literal){
    if (literal.m_lit.getTypeString() == "NIL"){
        returns.push("NIL");
        return;
    }
    returns.push(literal.m_lit.getLiteralString());
}

//PARENTHESIZE
void AstVisitor::parenthesize(std::string name, std::vector<Expr*> expr_list){
    returns.push("(" + name);
    for(Expr* expr: expr_list){
        returns.push(" ");
        expr->accept(*this);
    }   
    returns.push(")");
}

//AstPrinter print
void AstPrinter::print(Expr* expr){
    expr->accept(*this);
    std::string final = "";
    while (!returns.empty()){
        final += returns.front();
        returns.pop();
    }
    //return
    std::cout << final << std::endl;
}

//test main function
int main(){
    Binary* test = new Binary(
        new Unary(
            Token(TokenType::MINUS, "-", 0.0, 1),
            new Literal(Token(TokenType::NUMBER, "123", 123.0, 1))),
        Token(TokenType::STAR, "*", 0.0, 1),
        new Grouping(
            new Literal(Token(TokenType::NUMBER, "45,67", 45.67, 1)))
    );

    AstPrinter astprinter;
    astprinter.print(test);
}