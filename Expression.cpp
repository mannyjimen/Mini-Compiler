#include "Expression.hpp"

//constructors
Binary::Binary(std::shared_ptr<Expr> left, const Token& op, std::shared_ptr<Expr> right): m_left(left), m_op(op), m_right(right) {}

Literal::Literal(const LoxObject& lit): m_lit(lit) {}

Unary::Unary(const Token& logicalop, std::shared_ptr<Expr> operand): m_logicalop(logicalop), m_operand(operand) {}

Grouping::Grouping(std::shared_ptr<Expr> contents): m_contents(contents) {}
    
Variable::Variable(const Token& tokenName): m_tokenName{tokenName} {}

Assign::Assign(const Token& tokenName, std::shared_ptr<Expr> value): m_tokenName{tokenName}, m_value{value} {}

Logical::Logical(std::shared_ptr<Expr> left_operand, const Token& logica_op, std::shared_ptr<Expr> right_operand)
: m_left_operand(left_operand), m_logical_op(logica_op), m_right_operand(right_operand) {}

//accept implemenatations
void Binary::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}
void Literal::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}
void Unary::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}
void Grouping::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}
void Variable::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}

void Assign::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}

void Logical::accept(ExprVisitor& visitor){
    return visitor.visit(*this);
}

   
//AST ExprVisitor Implementations
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
void AstVisitor::parenthesize(const std::string& name, const std::vector<std::shared_ptr<Expr>>& expr_list){
    returns.push("(" + name);
    for(std::shared_ptr<Expr> expr: expr_list){
        returns.push(" ");
        expr->accept(*this);
    }   
    returns.push(")");
}

//AstPrinter print
void AstPrinter::print(std::shared_ptr<Expr> expr){
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