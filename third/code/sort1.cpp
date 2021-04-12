#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>


// 2 Choice
void bubbleSortVector(std::vector<int>& v) {
  int n = v.size();
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (v[j] > v[j+1]) {
        std::swap(v[j], v[j+1]);
      }
    }
  }
}

void bubbleSortVectorLog(std::vector<int>& v) {
  int n = v.size();
  int64_t comparisons = 0, swaps = 0;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      ++comparisons;
      if (v[j] > v[j+1]) {
        ++swaps;
        std::swap(v[j], v[j+1]);
      }
    }
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

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
    std::clog << "Start clock\n";
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

/*
void selectionSortVector(std::vector<int>& v) 
{ 
  int min_idx; 
  for (size_t i = 0; i < v.size() - 1; ++i) {
    min_idx = i;
    for (size_t j = i+1; j < v.size(); ++j) {
      if (v[j] < v[min_idx]) { 
        min_idx = j; 
      }
    }
    std::swap(v[min_idx], v[i]); 
  }
}
*/
void insertionSortVector(std::vector<int>& v) {
  for (size_t i = 1; i < v.size(); ++i) {
    for (size_t j = i; j > 0 && v[j] < v[j-1]; --j) {
      std::swap(v[j], v[j-1]);
    }
  }
}

void insertionSortVectorLog(std::vector<int>& v) {
  int64_t comparisons = 0, swaps = 0;
  for (size_t i = 1; i < v.size(); ++i) {
    for (size_t j = i; j > 0 && v[j] < v[j-1]; --j) {
      ++comparisons, ++swaps;
      std::swap(v[j], v[j-1]);
    }
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

void bubbleSortVectorAivLog(std::vector<int>& v) {
  bool isSorted = false;
  int n = v.size();
  int64_t comparisons = 0, swaps = 0;
  for (int i = 0; !isSorted && i < n - 1; ++i) {
    isSorted = true;
    for (int j = 0; j < n - i - 1; ++j) {
    ++comparisons;
      if (v[j] > v[j+1]) {
        ++swaps;
        std::swap(v[j], v[j+1]);
        isSorted = false;
      }
    }
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << "Please enter the size of an array:\n";
  int n;
  std::cin >> n;
  std::vector<int> arr(n);
  generateRandomVector(arr, n);
  {
    TimeCounter tc;
    insertionSortVectorLog(arr);
  }
  return 0;
}

