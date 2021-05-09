#include "search_algos.cpp"

int main() {
  constexpr auto file_name = "search_data.txt";
  std::ifstream fin;
  fin.open(file_name);
  std::vector<std::string> rows;
  for (std::string line; std::getline(fin, line);) {
    rows.push_back(line);
  }

  std::string result;
  std::cout << "Enter the key of the row:\n";
  int key;
  std::cin >> key;

  {
    TimeCounter tc;
    result = interpolationSearch(rows, key);
  }
  std::cout << result << '\n';

  fin.close();
  return 0;
}
