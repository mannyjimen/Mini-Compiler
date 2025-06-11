#include "ExpressionTypes.hpp"

//constructors
Binary::Binary(Expr* left, const Token& op, Expr* right){
        m_left = left;
        m_op = op;
        m_right = right;
}

Literal::Literal(const std::variant<bool, double, std::string>& lit){
    m_lit = lit;
}

Unary::Unary(const Token& logicalop, Expr* operand){
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
    //literal is boolean
    if(std::get_if<bool>(&literal.m_lit)){
        if(std::get<bool>(literal.m_lit) == 0){
            returns.push("false");
            return;
        }
        else{
            returns.push("true");
            return;
        }
    }
    //literal is double
    else if (std::get_if<double>(&literal.m_lit)){
        returns.push(std::to_string(std::get<double>(literal.m_lit)));
        return;
    }
    //literal is string
    returns.push(std::get<std::string>(literal.m_lit));
}

//PARENTHESIZE
void AstVisitor::parenthesize(const std::string& name, const std::vector<Expr*>& expr_list){
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
// int main(){
//     Binary* test = new Binary(
//         new Unary(
//             Token(TokenType::MINUS, "-", 0.0, 1),
//             new Literal(false)),
//         Token(TokenType::STAR, "*", 0.0, 1),
//         new Grouping(
//             new Literal(45.67))
//     );

//     Binary* test2 = new Binary(
//         new Unary(
//             Token(TokenType::MINUS, "-", 0.0, 1),
//             new Literal("HEY")),
//         Token(TokenType::STAR, "*", 0.0, 1),
//         new Binary(
//             new Unary(
//                 Token(TokenType::MINUS, "-", 0.0, 1),
//                 new Literal(123.0)),
//             Token(TokenType::STAR, "*", 0.0, 1),
//             new Grouping(
//                 new Literal(true))
            
//         )
//     );

//     Binary* test3 = new Binary(test, Token(TokenType::SLASH, "/", 0.0, 1), test2);


//     AstPrinter astprinter;
//     astprinter.print(test3);
// }