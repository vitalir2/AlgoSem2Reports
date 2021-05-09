#include "search_algos.cpp"

int main() {
  constexpr auto search_file_name = "search_data.txt";
  size_t key;
  std::cout << "Enter key to find in file" << '\n';
  std::cin >> key;
  std::string res;
  {
    TimeCounter tc;
    res = linearSearchFile(search_file_name, key);
  }
  std::cout << res << '\n';
  return 0;
}
