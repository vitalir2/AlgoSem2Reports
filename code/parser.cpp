#include <string>
#include <string_view>

class ProductParser {
public:
  std::string getCountryName(const std::string& data) const {
    std::string_view work_data(data);
    int begin = work_data.find_first_of(" ");
    int last = work_data.find_last_of(" ");
    return std::string(work_data.substr(begin, last - begin + 1));
    /*
    work_data.remove_prefix(work_data.find(' '));
    while (work_data.back() != ' ') {
      work_data.remove_suffix(1);
    }
    return std::string(work_data);
    */
  }
};
