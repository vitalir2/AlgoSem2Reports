#include <algorithm>
#include <iostream>
#include <locale>
#include <stack>
#include <string>
#include <utility>
#include <vector>

template<typename T>
class MyQueue final {
public:
  MyQueue() = default;
  ~MyQueue() {
    this->clear();
  }
  void push(const T& str) {
    Node* node = new Node();
    node->data = str;
    node->next = nullptr;
    if (begin == nullptr) {
      begin = (end = node);
    } else {
      end->next = node;
      end = node;
    }
    ++_size;
  }
  T pop() {
    if (begin == nullptr) {
      throw std::runtime_error("Pop on empty queue");
    }
    Node* node = begin;
    begin = begin->next;
    T str = node->data;
    delete node;
    --_size;
    return str;
  }
  T front() const {
    return begin->data;
  }
  T back() const {
    return end->data;
  }
  bool empty() const {
    return begin == nullptr;
  }
  void clear() {
    for (; begin != nullptr;) {
      Node* node = new Node();
      node = begin;
      begin=begin->next;
      delete node;
    }
  }
  T& operator[](size_t idx) {
    Node* node = begin;
    for (size_t i = 0; node->next != nullptr && i < idx; ++i, node=node->next);
    return node->data;
  }
  void print() const {
    for (Node* node = begin; node != nullptr; node=node->next) {
      std::cout << node->data << '\n';
    }
  }
  size_t size() const {
    return _size;
  }
private:
  struct Node {
    T data;
    Node* next;
  };
  Node* begin = nullptr;
  Node* end = nullptr; // not after end!
  size_t _size = 0;
};

// 5 + 2 -> 5 2 +
int calculatePrefix(const std::string& expression) {
  std::stack<int> stack;
  for (auto it = expression.crbegin(); it != expression.crend(); ++it) {
    if (std::isdigit(*it)) {
      stack.push(*it - '0');
    } else {
      int o1 = stack.top();
      stack.pop();
      int o2 = stack.top();
      stack.pop();
      switch(*it) {
        case '+':
          stack.push((o1 + o2));
          break;
        case '-':
          stack.push((o1 - o2));
          break;
        case '*':
          stack.push((o1 * o2));
          break;
        case '/':
          stack.push((o1 / o2));
          break;
      }
    }
  }
  return stack.top();
}

bool isdigit(const std::string& str) {
  for (char c: str) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return true;
}

int calculatePrefixQueue(MyQueue<std::string>& queue) {
  if (queue.size() == 1) {
    return std::stoi(queue.pop());
  }
  MyQueue<std::string> rec_queue;
  size_t old_size = queue.size();
  while (queue.size() > 0) {
    if (!isdigit(queue[0]) && isdigit(queue[1]) && isdigit(queue[2])) {
      char op = queue.pop().at(0);
      int o1 = std::stoi(queue.pop());
      int o2 = std::stoi(queue.pop());
      switch(op) {
        case '+':
          rec_queue.push(std::to_string(o1 + o2));
          break;
        case '-':
          rec_queue.push(std::to_string(o1 - o2));
          break;
        case '*':
          rec_queue.push(std::to_string(o1 * o2));
          break;
        case '/':
          rec_queue.push(std::to_string(o1 / o2));
          break;
      }
    } else {
      std::string element = queue.pop();
      rec_queue.push(element);
    }
  }
  if (old_size > rec_queue.size()) {
      return calculatePrefixQueue(rec_queue);
    } else {
      throw std::runtime_error("Wtf bro");
    }
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPrecidence(char c) {
  if (c == '*' || c == '/') {
    return 2;
  } else if (c == '-' || c == '+') {
    return 1;
  } else {
    return 0;
  }
}

// Shunting-yard algorithm
std::string convertFromInfixToPostfix(const std::string& expression) {
  std::stack<char> operators;
  std::string result = "";
  for (char token: expression) {
    if (std::isdigit(token) || std::isalpha(token)) {
      result += token;
    } else if (isOperator(token)) {
      while (!operators.empty()
          && getPrecidence(operators.top()) > getPrecidence(token)
          && operators.top() != '(') {
        result += operators.top();
        operators.pop();
      }
      operators.push(token);
    } else if (token == '(') {
      operators.push(token);
    } else if (token == ')') {
      while (operators.top() != '(') {
        result += operators.top();
        operators.pop();
      }
      if (operators.top() == '(') {
        operators.pop();
      }
    }
  }
  while (!operators.empty()) {
    result += operators.top();
    operators.pop();
  }
  return result;
}

void reverseParentheses(std::string& expression) {
  for (char& c: expression) {
    if (c == '(') {
      c = ')';
    } else if (c == ')') {
      c = '(';
    }
  }
}


std::string convertFromInfixToPrefix(const std::string& expression) {
  std::string result = expression;
  std::reverse(result.begin(), result.end());
  reverseParentheses(result);
  result = convertFromInfixToPostfix(result);
  std::reverse(result.begin(), result.end());
  return result;
}

enum class Order { LeftParenthesis, RightParenthesis};
void outputGroupOfParenthesesByOrder (const std::string& expression,
    Order order) {
  std::stack<int> left_par_ids;
  using parIds = std::pair<int, int>;
  std::vector<parIds> v;
  for (size_t i = 0; i < expression.size(); ++i) {
    if (expression[i] == '(') {
      left_par_ids.push(i+1);
    } else if (expression[i] == ')') {
      int left_id = left_par_ids.top();
      left_par_ids.pop();
      int right_id = i+1;
      v.push_back({left_id, right_id});
    }
  }
  if (order == Order::RightParenthesis) {
    std::sort(v.begin(), v.end(),[](const parIds& p1, const parIds& p2)
        { return p1.second < p2.second; });
  } else {
  std::sort(v.begin(), v.end(),[](const parIds& p1, const parIds& p2)
        { return p1.first < p2.first; });
  }
  for (const auto& elem: v) {
    std::cout << elem.first << ' ' << elem.second << "; ";
  }
  std::cout << '\n';
}
