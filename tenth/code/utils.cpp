#include <chrono>
#include <iostream>
#include <random>
#include <vector>

void generateRandomVector(std::vector<int>& v, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, upper_bound);
    for (int& elem: v) {
      elem = distrib(gen);
    }
}

void fillAscendVector(std::vector<int>& v) {
  int i = 0;
  for (int& elem: v) {
    elem = ++i;
  }
}

void fillDescendVector(std::vector<int>& v) {
  int i = std::numeric_limits<int>::max();
  for (int& elem: v) {
    elem = --i;
  }
}

template<typename T>
std::istream& operator>>(std::istream& stream, std::vector<T>& v) {
  for (T& elem: v) {
    stream >> elem;
  }
  return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& v) {
  for (const T& elem: v) {
    stream << elem << " ";
  }
  return stream;
}

class TimeCounter {
public:
  TimeCounter() {
//    std::clog << "Start clock\n";
    start = std::chrono::steady_clock::now();
  }
  ~TimeCounter() {
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::clog << "End clock, time = " << diff.count() << " ms" << std::endl;
  }
private:
  std::chrono::time_point<std::chrono::steady_clock> start;
};
