#include <iostream>
#include <string>
#include "parsing.cpp"

int main() {
  std::cout << "Enter expression in infix form: ";
  std::string expression;
  std::cin >> expression;
  std::cout << "Expression in prefix form: "
    << convertFromInfixToPrefix(expression) << '\n';
  return 0;
}
