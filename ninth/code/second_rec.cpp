#include <iostream>
#include <list>
#include <random>

constexpr int n = 10;

template<typename BidirIter>
void countEvenElementsListRec(BidirIter begin, BidirIter end, int& result) {
  if (begin != end) {
    if (*begin % 2 == 0) {
      ++result;
    }
    return countEvenElementsListRec(++begin, end, result);
  }
}

template<typename Number>
void generateRandomList(std::list<Number>& list) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<Number> dist(1, n);
  for (int i = 0; i < n; ++i) {
    list.push_back(dist(gen));
  }

}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::list<T>& list) {
  for (const auto& elem: list) {
    stream << elem << " ";
  }
  return stream;
}

int main() {
  int x = 0;
  std::list<int> list;
  generateRandomList(list);
  std::cout << "Random generated list: " << list << '\n';
  countEvenElementsListRec(list.cbegin(), list.cend(), x);
  std::cout << "Count of the even elements in list = " << x << '\n'; // the list, I know
  return 0;
}
