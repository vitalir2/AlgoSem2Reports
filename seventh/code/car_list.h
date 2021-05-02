#ifndef _CAR_LIST_H
#define _CAR_LIST_H
#include <iostream>
#include <string>

// I'm so lazy to create the iterator for this container
// + iterator to iterate only through specific models hmmm

struct CarNode {
  struct CarData {
    std::string car_model;
    std::string country;
    int year;
    friend std::ostream& operator<<(std::ostream& stream, const CarData& cdata);
  };
  CarData data;
  CarNode* prev;
  CarNode* next;
};

typedef CarNode::CarData CarData;

// Why I create this... (std::list: hello bro)
class ModelList {
  struct ModelNode {
    std::string model_name;
    CarNode* model_first;
    ModelNode* prev;
    ModelNode* next;
  };
public:
  void push_back(const std::string& name, CarNode* model_ptr);
  CarNode* getFirstNode(const std::string& name);
private:
  ModelNode* m_begin = nullptr;
  ModelNode* m_end = nullptr;
  size_t m_size = 0;
};

class CarList {
public:
  CarList() = default;
  ~CarList();

  void printList() const;
  void reversePrintList() const;

  void insert(const CarData& value, size_t pos);
  void insert(const CarData& value, CarNode* ptr);
  void push_front(const CarData& value);
  void push_back(const CarData& value);

  CarNode* searchByModel(const std::string& key) const;
  CarData& operator[](size_t pos);

  void sort();

  void delete_row(CarNode* node);
  void pop_back();
  void pop_front();

  // List should be already sorted, or the next functions won't work

  void insert_model(const CarData& car_data);
  ModelList createModelList() const;
  void delete_model(const std::string& model_name);
private:
  CarNode* m_begin = nullptr;
  CarNode* m_end = nullptr;
  size_t m_size = 0;
};
#endif // _CAR_LIST_H
