#include <iostream>
#include <fstream>
#include <string>
// string, string, int64_t
#include "generator.cpp"
#include "parser.cpp"
#include "sort_utilities.cpp"

namespace defined {
  constexpr char main_file_name[] = "test.txt";
  constexpr char buffer1_file_name[] = "b.txt";
  constexpr char buffer2_file_name[] = "c.txt";
  constexpr int64_t amount_of_lines = 1'000'000;//'000;
  constexpr long double some_strange_constant = 1.188;
}

void forwardDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t coef);
void forwardMerge(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t coef);

void forwardMergeSort(const std::string& input_name = defined::main_file_name,
    const std::string& buffer_name1 = defined::buffer1_file_name,
    const std::string& buffer_name2 = defined::buffer2_file_name,
    int64_t line_amount = defined::amount_of_lines) {
  for (int64_t coef = 1; coef < line_amount; coef <<= 1) {
    forwardDivision(input_name, buffer_name1, buffer_name2, coef);
    forwardMerge(input_name, buffer_name1, buffer_name2, coef);
  }
}

void forwardDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t coef) {
  std::ifstream fin;
  std::ofstream buff1, buff2;
  int counter = 0;
  std::string line, key;
  bool first_buff = true;

  fin.open(input_name);
  buff1.open(output_name1);
  buff2.open(output_name2);
  while (std::getline(fin, line)) {
    if (counter++ == coef) {
      first_buff = !first_buff;
      counter = 1;
    }
    (first_buff ? buff1 : buff2) << line << '\n';
  }
  fin.close(); buff1.close(); buff2.close();
}

void forwardMerge(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t coef) {
  std::ofstream fout;
  std::ifstream buff1, buff2;
  std::string line1, line2, country_name1, country_name2;
  bool buff1_end = false, buff2_end = false;
  ProductParser parser;

  fout.open(output_name);
  buff1.open(input_name1);
  buff2.open(input_name2);
      std::getline(buff1, line1); std::getline(buff2, line2);
  for (;;) {
  int64_t counter1 = 0, counter2 = 0;
    while (counter1 < coef && counter2 < coef) {
      if (!line1.empty() && !line2.empty()) {
        country_name1 = parser.getCountryName(line1);
        country_name2 = parser.getCountryName(line2);
      }
      if (country_name1 < country_name2) {
        ++counter1;
        fout << line1 << '\n';
        std::getline(buff1, line1);
        if (buff1.eof()) {
          buff1_end = true;
          break;
        }
      } else {
        ++counter2;
        fout << line2 << '\n';
        std::getline(buff2, line2);
        if (buff2.eof()) {
          buff2_end = true;
          break;
        }
      }
    }
    if (!buff1_end) {
      for (; counter1 < coef; ++counter1) {
        fout << line1 << '\n';
        std::getline(buff1, line1);
        if (buff1.eof()) {
          buff1_end = true;
          break;
        }
      }
    }
    if (!buff2_end) {
      for (; counter2 < coef; ++counter2) {
        fout << line2 << '\n';
        std::getline(buff2, line2);
        if (buff2.eof()) {
          buff2_end = true;
          break;
        }
      }
    }
    if (buff1_end || buff2_end) {
      break;
    }
  }
  if (!buff1_end) {
    while (std::getline(buff1, line1)) {
      fout << line1 << '\n';
    }
  }
  if (!buff2_end) {
    while (std::getline(buff2, line2)) {
      fout << line2 << '\n';
    }
  }

  fout.close(); buff1.close(); buff2.close();
}

void forwardDivisionLog(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t coef, int64_t& comparisons, int64_t& moves);
void forwardMergeLog(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t coef, int64_t& comparisons, int64_t& moves);

void forwardMergeSortLog(const std::string& input_name = defined::main_file_name,
    const std::string& buffer_name1 = defined::buffer1_file_name,
    const std::string& buffer_name2 = defined::buffer2_file_name,
    int64_t line_amount = defined::amount_of_lines) {
  int64_t comparisons = 0, moves = 0;
  for (int64_t coef = 1; coef < line_amount; coef <<= 1) {
    forwardDivisionLog(input_name, buffer_name1, buffer_name2, coef,
        comparisons, moves);
    forwardMergeLog(input_name, buffer_name1, buffer_name2, coef,
        comparisons, moves);
  }
  std::clog << "Comparisons: " << comparisons << std::endl;
  std::clog << "Moves: " << moves << std::endl;
  std::clog << "T_prac: " << comparisons + moves << std::endl;
}

void forwardDivisionLog(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t coef, int64_t& comparisons, int64_t& moves) {
  std::ifstream fin;
  std::ofstream buff1, buff2;
  int counter = 0;
  std::string line, key;
  bool first_buff = true;

  fin.open(input_name);
  buff1.open(output_name1);
  buff2.open(output_name2);
  while (std::getline(fin, line)) {
    if (counter++ == coef) {
      first_buff = !first_buff;
      counter = 1;
    }
    (first_buff ? buff1 : buff2) << line << '\n';
  }
  fin.close(); buff1.close(); buff2.close();
}

void forwardMergeLog(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t coef, int64_t& comparisons, int64_t& moves) {
  std::ofstream fout;
  std::ifstream buff1, buff2;
  std::string line1, line2, country_name1, country_name2;
  bool buff1_end = false, buff2_end = false;
  ProductParser parser;

  fout.open(output_name);
  buff1.open(input_name1);
  buff2.open(input_name2);
      std::getline(buff1, line1); std::getline(buff2, line2);
  for (;;) {
  int64_t counter1 = 0, counter2 = 0;
    while (counter1 < coef && counter2 < coef) {
      comparisons += 2; ++moves;
      if (!line1.empty() && !line2.empty()) {
        country_name1 = parser.getCountryName(line1);
        country_name2 = parser.getCountryName(line2);
      }
      if (country_name1 < country_name2) {
        ++counter1;
        fout << line1 << '\n';
        std::getline(buff1, line1);
        if (buff1.eof()) {
          buff1_end = true;
          break;
        }
      } else {
        ++counter2;
        fout << line2 << '\n';
        std::getline(buff2, line2);
        if (buff2.eof()) {
          buff2_end = true;
          break;
        }
      }
    }
    if (!buff1_end) {
      for (; counter1 < coef; ++counter1) {
        fout << line1 << '\n';
        ++moves;
        std::getline(buff1, line1);
        if (buff1.eof()) {
          buff1_end = true;
          break;
        }
      }
    }
    if (!buff2_end) {
      for (; counter2 < coef; ++counter2) {
        fout << line2 << '\n';
        ++moves;
        std::getline(buff2, line2);
        if (buff2.eof()) {
          buff2_end = true;
          break;
        }
      }
    }
    if (buff1_end || buff2_end) {
      break;
    }
  }
  if (!buff1_end) {
    while (std::getline(buff1, line1)) {
      fout << line1 << '\n';
      ++moves;
    }
  }
  if (!buff2_end) {
    while (std::getline(buff2, line2)) {
      fout << line2 << '\n';
      ++moves;
    }
  }

  fout.close(); buff1.close(); buff2.close();
}

void firstNaturalDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
     int64_t n);

void naturalDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2);

void naturalMerge(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t n, int64_t& groups);

void naturalMergeSort(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t n) {
  int64_t series;
  firstNaturalDivision(input_name, output_name1, output_name2, n);
  for (;;) {
    series = 0;
    naturalMerge(input_name, output_name1, output_name2, n, series);
    if (series == 1) {
      break;
    }
    naturalDivision(input_name, output_name1, output_name2);
  }
}

void firstNaturalDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
     int64_t n) {
  std::ifstream fin;
  std::ofstream buff1, buff2;
  std::string line, key;
  ProductParser parser;
  std::vector<std::string> buf;
  buf.reserve(n);

  fin.open(input_name);
  buff1.open(output_name1);
  buff2.open(output_name2);
 
  for (int i = 0; i < n / 2; ++i) {
    std::getline(fin, line);
    buf.push_back(line);
  }
  std::sort(buf.begin(), buf.end(), [parser](const std::string& line1, const std::string& line2)
      { return parser.getCountryName(line1) < parser.getCountryName(line2); });
  for (const std::string& line: buf) {
    buff1 << line << '\n';
  }
  buf.clear();
 
  for (int i = 0; i < n / 2; ++i) {
    std::getline(fin, line);
    buf.push_back(line);
  }
  std::sort(buf.begin(), buf.end(), [parser](const std::string& line1, const std::string& line2)
      { return parser.getCountryName(line1) < parser.getCountryName(line2); });
  for (const std::string& line: buf) {
    buff2 << line << '\n';
  }

  fin.close(); buff1.close(); buff2.close();
}

void naturalDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2) {
  std::ifstream fin;
  std::ofstream buff1, buff2;
  std::string line, key;
  bool first_buff = true;

  fin.open(input_name);
  buff1.open(output_name1);
  buff2.open(output_name2);
  while (std::getline(fin, line) && !line.empty()) {
    (first_buff ? buff1 : buff2) << line << '\n';
    first_buff = !first_buff;
  }
  fin.close(); buff1.close(); buff2.close();
}

void naturalMerge(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t n, int64_t& groups) {
  std::ofstream fout;
  std::ifstream buff1, buff2;
  std::string line1, line2, country_name1, country_name2;
  ProductParser parser;

  fout.open(output_name);
  buff1.open(input_name1);
  buff2.open(input_name2);

  for (int64_t counter = 0 ;counter < n; ++groups) {
    std::getline(buff1, line1);
    std::getline(buff2, line2);

    for (;!line1.empty() && !line2.empty();++counter) {
      country_name1 = parser.getCountryName(line1);
      country_name2 = parser.getCountryName(line2);
      if (country_name1 < country_name2) {
        fout << line1 << '\n';
        std::getline(buff1, line1);
      } else {
        fout << line2 << '\n';
        std::getline(buff2, line2);
      }
    }
     for (; !line1.empty(); ++counter) {
        fout << line1 << '\n';
        std::getline(buff1, line1);
      }
      for (; !line2.empty(); ++counter) {
        fout << line2 << '\n';
        std::getline(buff2, line2);
    }
  }
  fout.close(); buff1.close(); buff2.close();
}

void firstNaturalDivision(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
     int64_t n);

void naturalDivisionLog(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t& moves);
void naturalMergeLog(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t n, int64_t& groups, int64_t& comparisons, int64_t& moves);

void naturalMergeSortLog(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t n) {
  int64_t series;
  int64_t comparisons = 0, moves = 0;

  // Compensation for quick sort two times in firstNaturalDivision
  long double coeff = defined::some_strange_constant*n*std::log(n);
  comparisons += 2 * static_cast<int64_t>(coeff);
  moves += 2 * static_cast<int64_t>(coeff / 5);

  firstNaturalDivision(input_name, output_name1, output_name2, n);
  for (;;) {
    series = 0;
    naturalMergeLog(input_name, output_name1, output_name2, n,
        series, comparisons, moves);
    if (series == 1) {
      break;
    }
    naturalDivisionLog(input_name, output_name1, output_name2, moves);
  }
  std::clog << "Comparisons: " << comparisons << std::endl;
  std::clog << "Moves: " << moves << std::endl;
  std::clog << "T_prac: " << comparisons + moves << std::endl;
}

void naturalDivisionLog(const std::string& input_name,
    const std::string& output_name1, const std::string& output_name2,
    int64_t& moves) {
  std::ifstream fin;
  std::ofstream buff1, buff2;
  std::string line, key;
  bool first_buff = true;

  fin.open(input_name);
  buff1.open(output_name1);
  buff2.open(output_name2);
  while (std::getline(fin, line) && !line.empty()) {
    ++moves;
    (first_buff ? buff1 : buff2) << line << '\n';
    first_buff = !first_buff;
  }
  fin.close(); buff1.close(); buff2.close();
}

void naturalMergeLog(const std::string& output_name,
    const std::string& input_name1, const std::string& input_name2,
    int64_t n, int64_t& groups, int64_t& comparisons, int64_t& moves) {
  std::ofstream fout;
  std::ifstream buff1, buff2;
  std::string line1, line2, country_name1, country_name2;
  ProductParser parser;

  fout.open(output_name);
  buff1.open(input_name1);
  buff2.open(input_name2);

  for (int64_t counter = 0 ;counter < n; ++groups) {
    std::getline(buff1, line1);
    std::getline(buff2, line2);

    for (;!line1.empty() && !line2.empty();++counter) {
      country_name1 = parser.getCountryName(line1);
      country_name2 = parser.getCountryName(line2);
      ++comparisons;
      if (country_name1 < country_name2) {
        fout << line1 << '\n';
        ++moves;
        std::getline(buff1, line1);
      } else {
        fout << line2 << '\n';
        ++moves;
        std::getline(buff2, line2);
      }
    }
     for (; !line1.empty(); ++counter) {
        fout << line1 << '\n';
        ++moves;
        std::getline(buff1, line1);
      }
      for (; !line2.empty(); ++counter) {
        fout << line2 << '\n';
        ++moves;
        std::getline(buff2, line2);
    }
  }
  fout.close(); buff1.close(); buff2.close();
}

int main() {
  int n;
  std::cout << "Enter the size of an array: ";
  std::cin >> n;
  Generator gen;
  gen.generate(n);
  {
    TimeCounter tc;
    naturalMergeSortLog("test.txt", "b.txt", "c.txt", n);
  }
  return 0;
}
