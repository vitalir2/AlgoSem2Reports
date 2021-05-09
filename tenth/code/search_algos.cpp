#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.cpp"

// it pollutes global namespace but not a real code so ...
constexpr auto no_key = "No key";

int parseKey(const std::string& line) {
  auto pos = std::find(line.begin(), line.end(), ' ');
  std::string res_string = std::string(line.begin(), pos);
  return std::stoi(res_string);
}

std::string linearSearchFile(const std::string& file_name, int key) {
  std::ifstream fin;
  fin.open(file_name);
  std::string line;
  while (std::getline(fin, line)) {
    if (parseKey(line) == key) {
      return line;
    }
  }
  return no_key;
}

std::string interpolationSearch(const std::vector<std::string>& rows, int key) {
  size_t low = 0;
  size_t high = rows.size() - 1;
  size_t mid = 0;

  while (rows[high] != rows[low] && key >= parseKey(rows[low])
      && key <= parseKey(rows[high])) {
    mid = low + ((key - parseKey(rows[low])) * (high - low)
        / (parseKey(rows[high]) - parseKey(rows[low])));

    if (parseKey(rows[mid]) < key) {
      low = mid + 1;
    } else if (key < parseKey(rows[mid])) {
      high = mid - 1;
    } else {
      return rows[mid];
    }
  }
  if (key == parseKey(rows[low])) {
    return rows[low];
  } else {
    return no_key;
  }
}
