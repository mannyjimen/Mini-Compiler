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


std::string AstVisitor::visitBinary(Binary& binary){
    return parenthesize(binary.m_op.getLexeme(), {binary.m_left, binary.m_right});
}

std::string AstVisitor::visitLiteral(Literal& literal){
    if (literal.m_lit.getTypeString() == "NIL") return "NIL";
    return literal.m_lit.getLiteralString();
}

std::string AstVisitor::visitUnary(Unary& unary){
    return parenthesize(unary.m_logicalop.getLexeme(), {unary.m_operand});
}

std::string AstVisitor::visitGrouping(Grouping& grouping){
   return parenthesize("group", {grouping.m_contents});
}

std::string AstVisitor::parenthesize(std::string name, std::vector<Expr*> expr_list){
    std::string final = "(";
    for(Expr* expr: expr_list){
        final += " ";
        final += expr->acceptAstPrint(*this);
    }   
    final += ")";

    return final;
}

int main(){
    Binary* test = new Binary(
        new Unary(
            Token(TokenType::MINUS, "-", 0.0, 1),
            new Literal(Token(TokenType::NUMBER, "123", 123.0, 1))),
        Token(TokenType::STAR, "*", 0.0, 1),
        new Grouping(
            new Literal(Token(TokenType::NUMBER, "45,67", 45.67, 1)))
    );

    std::cout << (new AstPrinter)->print(test);
}