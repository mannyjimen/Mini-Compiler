#include "lexer.hpp"

int main()
{
    Lexer Hello("firstcode;2+2=4;lol;");
    Hello.printTokens();
}