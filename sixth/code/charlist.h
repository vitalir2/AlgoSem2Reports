#include <string>

class CharList {
public:
  struct CharNode {
      char value;
      CharNode* next; 
    };
 
  CharList();
  CharList(char new_value);
  CharList(const std::string& word);

  ~CharList();

  CharNode* insert_after(char new_value, int pos);
  CharNode* insert_after(char new_value, int pos, int count);
  CharNode* insert_after(char new_value, CharNode* ptr);
  CharNode* insert_before(char new_value, int pos);
  CharNode* insert_before(char new_value, CharNode* ptr);
  void push_back(char new_value);

  CharNode* insert_word_after(const std::string& word, int pos);
  CharNode* insert_word_after(const std::string& word, CharNode* p);
  CharNode* insert_word_before(const std::string& word, int pos); 
  CharNode* insert_word_before(const std::string& word, CharNode* p); 
  void push_back(const std::string& word);

  CharNode* delete_after(int pos);
  CharNode* delete_after(CharNode* ptr);
  void pop_front();

  CharNode* delete_word(int word_pos);
  CharNode* delete_second_word();

  CharNode* replace_word(const std::string& word, int pos); 

  void moveLastToBeginning();
  void moveLastWordToBeginning();

  void printList() const;

  inline size_t getSize() const {
    return size;
  }

  int amountOfWords();
private:
   CharNode* root = nullptr;
   size_t size = 0;

   CharNode* end() const;
};
