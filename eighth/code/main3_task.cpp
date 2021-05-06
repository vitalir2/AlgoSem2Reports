#include <iostream>
#include <string>

#include "parsing.cpp"

int main() {
  std::string expression;
  std::cout << "Enter an expression to parse its parantheses: ";
  std::cin >> expression;
  std::cout << "Enter the number to set order in which parantheses"
    << " indexes will be print on the screen:\n"
    << "1 - opening parantheses, 2 - close one\n";
  int order_num;
  std::cin >> order_num;
  switch(order_num) {
    case 1: outputGroupOfParenthesesByOrder(expression,
                Order::LeftParenthesis);
            break;
    case 2: outputGroupOfParenthesesByOrder(expression,
                Order::RightParenthesis);
            break;
  }
  return 0;
}
