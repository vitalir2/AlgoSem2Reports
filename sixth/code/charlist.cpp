// I think I need to change the structure (add the element before the first
// to use my operations)
#include <iostream>
#include <string>

#include "charlist.h"

CharList::CharList() = default;

CharList::CharList(char new_value) {
  insert_before(new_value, 0);
}

CharList::CharList(const std::string& word) {
  insert_word_before(word, 0);
}

CharList::~CharList() {
  for (;root != nullptr;) {
    CharNode* ptr = root;
    root = root->next;
    delete ptr;
  }
}

CharList::CharNode* CharList::insert_after(char new_value, int pos) {
  CharNode* ptr = root;
  for (int i = 0; i < pos && ptr->next != nullptr; ++i, ptr = ptr->next) {
  }
  CharNode* node = new CharNode();
  ++size;
  node->value = new_value;
  node->next = ptr->next;
  ptr->next = node;
  return node;
}

CharList::CharNode* CharList::insert_after(char new_value, CharNode* ptr) {
  CharNode* node = new CharNode();
  ++size;
  node->value = new_value;
  node->next = ptr->next;
  ptr->next = node;
  return node;
}

CharList::CharNode* CharList::insert_after(char new_value, int pos, int count) {
  CharNode* node;
  for (int i = 0; i < count; ++i) {
    node = insert_after(new_value, pos+i);
  }
  return node;
}

CharList::CharNode* CharList::insert_before(char new_value, int pos) { // before nullptr?
  CharNode* ptr = root;
  for (int i = 0; i < pos && ptr->next != nullptr; ++i, ptr = ptr->next) {
  }
  CharNode* node = new CharNode();
  ++size;
  if (ptr != nullptr) {
    node->value = ptr->value;
    node->next = ptr->next;
    ptr->value = new_value;
    ptr->next = node;
    return ptr;
  } else {
    root = node;
    node->value = new_value;
    node->next = nullptr;
    return node;
  }
}

CharList::CharNode* CharList::insert_before(char new_value, CharNode* ptr) {
  CharNode* node = new CharNode();
  ++size;
  if (ptr != nullptr) {
    node->value = ptr->value;
    node->next = ptr->next;
    ptr->value = new_value;
    ptr->next = node;
    return ptr;
  } else {
    root = node;
    node->value = new_value;
    node->next = nullptr;
    return node;
  }
}
void CharList::push_back(char new_value) {
  insert_after(new_value, end());
}

CharList::CharNode* CharList::insert_word_after(const std::string& word, int pos) {
  CharNode* node;
  for (int i = 0; i < static_cast<int>(word.size()); ++i) {
    node = insert_after(word[i], pos+i);
  }
  return node;
}

CharList::CharNode* CharList::insert_word_after(const std::string& word, CharNode* p) {
  CharNode* node = p;
  for (int i = 0; i < static_cast<int>(word.size()); ++i) {
    node = insert_after(word[i], node);
  }
  return node;
}

void CharList::push_back(const std::string& word) {
  insert_word_after(word, end());
}

CharList::CharNode* CharList::insert_word_before(const std::string& word, int pos) {
  CharNode* node;
  node = insert_before(word[0], pos);
  for (int i = 1; i < static_cast<int>(word.size()); ++i) {
    node = insert_after(word[i], pos+i);
  }
  return node;
}

CharList::CharNode* CharList::insert_word_before(const std::string& word, CharNode* p) {
  CharNode* node = p;
  node = insert_before(word[0], p);
  for (int i = 1; i < static_cast<int>(word.size()); ++i) {
    node = insert_after(word[i], node);
  }
  return node;
}

CharList::CharNode* CharList::delete_after(int pos) {
  CharNode* ptr = root;
  for (int i = 0; i < pos && ptr->next != nullptr; ++i, ptr = ptr->next);
  if (ptr->next != nullptr) {
    CharNode* p = ptr->next;
    ptr->next = p->next;
    delete p;
    --size;
  }
  return ptr;
}

CharList::CharNode* CharList::delete_after(CharNode* ptr) {
  if (ptr->next != nullptr) {
    CharNode* p = ptr->next;
    ptr->next = p->next;
    delete p;
    --size;
  }
  return ptr;
}

void CharList::pop_front() {
  if (root->next != nullptr) {
    CharNode* ptr = root;
    root = root->next;
    delete ptr;
  }
}

CharList::CharNode* CharList::delete_word(int word_pos) {
  CharNode* ptr = root;
  for (int i = 1; i < word_pos; ++i) {
    for (;ptr->value != ' '; ptr = ptr->next);
    if (ptr->next != nullptr && i != word_pos-1) {
      ptr = ptr->next;
    }
  }
  if (word_pos == 1) {
    for (;root->value != ' ';) {
      this->pop_front();
    }
    this->pop_front();
    return root;
  }
  for (; ptr->next != nullptr && ptr->next->value != ' ';) {
    delete_after(ptr);
  }
  if (ptr->next != nullptr) {
    delete_after(ptr);
  }
  return ptr;
}

CharList::CharNode* CharList::delete_second_word() {
  return delete_word(2);
}

CharList::CharNode* CharList::replace_word(const std::string& word, int pos) {
  int amount = amountOfWords();
  CharNode* ptr = delete_word(pos);
  if (pos == 1) {
    ptr = insert_word_before(word, ptr);
  } else {
    ptr = insert_word_after(word, ptr);
  }
  if (pos == amount) {
    return ptr;
  }
  return insert_after(' ', ptr);
}

// Amount of the spaces + 1 = amount of the words in the list
int CharList::amountOfWords() {
  int amount = 0;
  for (CharNode* ptr = root; ptr != nullptr; ptr = ptr->next) {
    if (ptr->value == ' ') {
      ++amount;
    }
  }
  return amount + 1;
}

void CharList::moveLastToBeginning() {
  CharNode* ptr = end();
  char val = ptr->value;
  delete_after(size-2);
  insert_before(val, 0);
}

CharList::CharNode* CharList::end() const {
  CharNode* ptr = root;
  for (;ptr->next != nullptr; ptr = ptr->next);
  return ptr;
}

// can move with only swapping values?

void CharList::moveLastWordToBeginning() {
  int shift = 0;
  for (;end()->value != ' '; ++shift) {
    moveLastToBeginning();
  }
  insert_before(' ', shift);
  delete_after(size-2);
}

void CharList::printList() const {
  CharNode* ptr = root;
  for (;ptr != nullptr;ptr = ptr->next) {
    if (ptr->value == ' ') {
      std::cout << '_';
    } else {
      std::cout << ptr->value;
    }
  }
}
