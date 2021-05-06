#include <iostream>
#include <string>
#include "parsing.cpp"

int main() {
  MyQueue<std::string> queue;
  std::string expression;
  std::cout << "Enter an expression in prefix form: ";
  std::cin >> expression;
  for (char c: expression) {
    std::string str(1, c);
    queue.push(str);
  }
  std::cout << "Value of the expression = " << calculatePrefixQueue(queue) << '\n';
  return 0;
}
