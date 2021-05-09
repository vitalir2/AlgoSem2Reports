#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

constexpr int error_code = 2;
// not work with g++ now =( constexpr std::string standard_file_name = "search_data.txt";
constexpr auto standard_file_name = "search_data.txt"; // auto = char[]

const std::vector<std::string> insurance_companies_names = {"Aflac",
  "Acuity_Insurance", "Allianz_life", "Allstate", "Berkshire_Hathaway",
  "CareSource", "Chubb_Corp", "CNO_Financial", "Delta_Dental",
  "Erie_Insurance_Group", "Esurance", "Evergreen", "FM_Global",
  "GAINSCO", "GEICO", "General_Re", "Hanover_Insurance",
  "Ironshore", "K&K_Insurance", "Kemper_Corporation",
  "Knights_of_Columbus", "Lemonade_Inc", "Liberty_Mutual",
  "MassMutual", "MetLife", "Metromile", "Modern_Woodmen_of_America",
  "Omega", "OneBeacon", "Pacific_Life", "PEMCO", "Penn_Mutual",
  "Primerica", "Progressive", "Protective_Life", "Pure_Insurance",
  "QBE", "Safeco", "Society_Insurance", "SquareTrade", "Symetra",
  "The_General", "TIAA-CREF", "Tricare", "Trupanion", "Unum",
  "USAA", "West_Coast_Life", "XL_Catlin", "Zurich_Insurance_Group"};

using DataRow = std::pair<int, std::string>;

DataRow getRandomRow() noexcept;
void generateFile(const std::string& file_name, int row_number);
int parseNumber(const std::string& line);
void sortFile(const std::string& file_name);

// because it's created many times
// so static allows program not to create objects again
DataRow getRandomRow() noexcept {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<int> strDist(0, insurance_companies_names.size() - 1);

  static const int lower_bound = 100'000;
  static const int upper_bound = 999'999;
  static std::uniform_int_distribution<int> numDist(lower_bound, upper_bound);

  return {numDist(gen), insurance_companies_names[strDist(gen)]};
}

void generateFile(const std::string& file_name, int row_number) {
  // not right to create in this function fout 
  // (function must do only one task! PS: Clean Code)
  std::vector<DataRow> rows(row_number);
  for (DataRow& row: rows) {
    row = getRandomRow();
  }

  try {
    std::ofstream fout;
    fout.open(file_name);
    for (const auto& [number, name]: rows) {
      fout << number << " " << name << '\n';
    }
    fout.close();
  } catch(std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    std::exit(error_code);
  }
}

int parseNumber(const std::string& line) {
  auto pos = std::find(line.begin(), line.end(), ' ');
  std::string res_string = std::string(line.begin(), pos);
  return std::stoi(res_string);
}

void sortFile(const std::string& file_name) {
  std::vector<std::string> file_rows;

  std::ifstream fin;
  try {
    fin.open(file_name);
    std::string line;
    while (std::getline(fin, line)) {
      file_rows.push_back(line);
    }
    fin.close();
  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    std::exit(error_code);
  }

  auto lineComparison = [](const std::string& first, const std::string& second)
  { return parseNumber(first) < parseNumber(second); };
  std::sort(file_rows.begin(), file_rows.end(), lineComparison);

  std::ofstream fout;
  try {
    std::ofstream fout;
    fout.open(file_name);
    for (const std::string& row: file_rows) {
      fout << row << '\n';
    }
    fout.close();
  } catch(std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    std::exit(error_code);
  }

}

int main() {
  int row_number;
  std::cout << "Enter the row number of a new file:\n";
  std::cin >> row_number;


  std::cout << "Sorted file was created successfully\n";
  return 0;
}
