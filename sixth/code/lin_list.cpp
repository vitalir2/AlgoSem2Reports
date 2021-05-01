#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <string_view>

#include "charlist.h"

const std::string lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris\
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in\
reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla\
pariatur. Excepteur sint occaecat cupidatat non proident, sunt in\
culpa qui officia deserunt mollit anim id est laborum.";

template<typename Stream>
void debugList(const CharList& list, Stream& stream) {
  list.printList();
  stream << std::endl;
}

void debugOutputList(const CharList& list, const std::string& message) {
  std::cout << message;
  list.printList();
  std::cout << '\n';
}

std::vector<std::string> createLoremWords() {
  std::vector<std::string> lorem_words;
  std::string_view sv(lorem);
  for (; sv.find(' ') != std::string_view::npos;
      sv.remove_prefix(sv.find(' ') + 1)) {
    lorem_words.push_back(std::string(sv.substr(0, sv.find(' '))));
  }
  lorem_words.push_back(std::string(sv));
  return lorem_words;
}

std::string getRandomLoremWord(const std::vector<std::string>& lorem_words) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, lorem_words.size());
  return lorem_words[dist(gen)];
}

int main() {
  std::vector<std::string> lorem_words = createLoremWords();
  for (int i = 0; i < 5; ++i) {
    CharList list("Hello ");
    for (int k = 0; k < 5; ++k) {
      list.push_back(getRandomLoremWord(lorem_words));
      if (k != 4) {
        list.push_back(' ');
      }
    }
    debugList(list, std::cout);
    list.moveLastWordToBeginning();
    debugOutputList(list, "Last word moved to the beginning: ");
    list.delete_second_word();
    debugOutputList(list, "Second word was deleted: ");
    auto lorem_word = getRandomLoremWord(lorem_words);
    list.replace_word(lorem_word, i + 1);
    debugOutputList(list, "Word " + std::to_string(i+1)
        + " was replaced by " + lorem_word + " : ");
    std::cout << std::endl;
  }
  return 0;
}
