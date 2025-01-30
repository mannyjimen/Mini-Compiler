#include "Lox.hpp"

int main()
{
    std::string decider;
    std::cout << "Enter filename, or press ENTER for prompt: \n";
    std::cin >> decider;
    Lox program(decider);
}