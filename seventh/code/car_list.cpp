#include <iostream>
#include <string>
#include <vector>

#include "car_list.h"

// I'm so lazy to create the iterator for this container
// + iterator to iterate only through specific models hmmm
// Also...

std::ostream& operator<<(std::ostream& stream, const CarData& cdata) {
  stream << cdata.car_model << " " << cdata.country
    << " " << cdata.year;
  return stream;
}

typedef CarNode::CarData CarData;

void ModelList::push_back(const std::string& name, CarNode* model_ptr) {
  ModelNode* node = new ModelNode();
  node->model_name = name;
  node->model_first = model_ptr;
  node->next = nullptr;
  node->prev = m_end;
  if (m_end != nullptr) {
    m_end->next = node;
  } else {
    m_begin = (m_end = node);
  }
  m_end = node;
  ++m_size;
}

CarNode* ModelList::getFirstNode(const std::string& name) {
  for (ModelNode* ptr = m_begin; ptr != nullptr; ptr = ptr->next) {
    if (ptr->model_name == name) {
      return ptr->model_first;
    }
  }
  return nullptr;
}

CarList::~CarList() {
  for (CarNode* ptr = m_begin; ptr != nullptr;) {
    CarNode* p = ptr;
    ptr = ptr->next;
    delete p;
  }
}
void CarList::printList() const {
  for (CarNode* ptr = m_begin; ptr != nullptr; ptr = ptr->next) {
    std::cout << ptr->data << '\n';
  }
}

void CarList::push_back(const CarData& value) {
  CarNode* node = new CarNode();
  node->data = value;
  node->next = nullptr;
  node->prev = m_end;
  if (m_end != nullptr) {
    m_end->next = node;
  } else {
    m_begin = (m_end = node);
  }
  m_end = node;
  ++m_size;
}

void CarList::push_front(const CarData& value) {
  CarNode* node = new CarNode();
  node->data = value;
  node->prev = nullptr;
  node->next = m_begin;
  if (m_begin != nullptr) {
    m_begin->prev = node;
  } else {
    m_begin = (m_end = node);
  }
  m_begin = node;
  ++m_size;
}

// I can speed up this algo ~ in two times, but I have no time for games =)
// Insert before the position
void CarList::insert(const CarData& value, size_t pos) {
  if (pos == 0) {
    return push_front(value);
  }
  CarNode* node = new CarNode();
  CarNode* ptr = m_begin;
  for (size_t i = 0; i < pos; ++i, ptr = ptr->next);
  node->data = value;
  node->next = ptr;
  if (ptr == nullptr) {
    node->prev = nullptr;
    m_begin = m_end = node;
    return;
  }
  node->prev = ptr->prev;
  if (ptr->prev != nullptr) {
    ptr->prev->next = node;
  }
  ptr->prev = node;
  ++m_size;
}

void CarList::insert(const CarData& value, CarNode* ptr) {
  if (ptr == m_begin) {
    return push_front(value);
  }
  CarNode* node = new CarNode();
  node->data = value;
  node->next = ptr;
  if (ptr == nullptr) {
    node->prev = nullptr;
    m_begin = m_end = node;
    return;
  }
  node->prev = ptr->prev;
  if (ptr->prev != nullptr) {
    ptr->prev->next = node;
  }
  ptr->prev = node;
  ++m_size;
}


void CarList::reversePrintList() const {
  for (CarNode* ptr = m_end; ptr != nullptr; ptr=ptr->prev) {
    std::cout << ptr->data << '\n';
  }
}

CarNode* CarList::searchByModel(const std::string& key) const {
  for (CarNode* ptr = m_begin; ptr != nullptr; ptr=ptr->next) {
    if (ptr->data.car_model == key) {
      return ptr;
    }
  }
  return nullptr;
}

// Quick sort algo
void CarList::sort() {
  std::vector<CarData> v;
  for (CarNode* ptr = m_begin; ptr != nullptr; ptr=ptr->next) {
    v.push_back(std::move(ptr->data));
  }

  std::sort(v.begin(), v.end(), [](const CarData& c1, const CarData& c2)
      { return c1.car_model < c2.car_model; });

  std::string prev_name = "";
  auto prev_it = v.begin();
  int counter = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (prev_name != it->car_model) {
      std::sort(prev_it, prev_it + counter,
          [](const CarData& c1, const CarData& c2)
          { return c1.year < c2.year; });
      counter = 0;
      prev_it = it;
      prev_name = it->car_model;
    }
    ++counter;
  }
  std::sort(prev_it, prev_it + counter,
          [](const CarData& c1, const CarData& c2)
          { return c1.year < c2.year; });

  auto it = v.cbegin();
  for (CarNode* ptr = m_begin; ptr != nullptr; ptr=ptr->next, ++it) {
    ptr->data = std::move(*it);
  }
}

CarData& CarList::operator[](size_t pos) {
  CarNode* ptr = m_begin;
  for (size_t i = 0; ptr != nullptr && i < pos; ++i, ptr=ptr->next);
  return ptr->data;
}

// List should be already sorted, or the next functions won't work

void CarList::insert_model(const CarData& car_data) {
  ModelList model_list = createModelList();
  CarNode* node = model_list.getFirstNode(car_data.car_model);
  auto ptr = node;
  for (; ptr != nullptr && node->data.car_model == ptr->data.car_model; ptr=ptr->next) {
    if (car_data.year < ptr->data.year) {
      this->insert(car_data, ptr);
      return;
    }
  }
  if (ptr != nullptr) {
    this->insert(car_data, ptr);
  } else {
    this->push_back(car_data);
  }
}

ModelList CarList::createModelList() const {
  ModelList model_list;
  std::string prev_name = "";
  for (auto ptr = m_begin; ptr != nullptr; ptr=ptr->next) {
    if (prev_name != ptr->data.car_model) {
      model_list.push_back(ptr->data.car_model, ptr);
      prev_name = ptr->data.car_model;
    }
  }
  return model_list;
}

void CarList::delete_model(const std::string& model_name) {
  ModelList model_list = createModelList();
  CarNode* node = model_list.getFirstNode(model_name);
  for (auto ptr = node; ptr != nullptr && model_name == ptr->data.car_model;) {
    CarNode* p = ptr;
    ptr = ptr->next;
    this->delete_row(p);
  }
}

void CarList::delete_row(CarNode* node) {
  if (node == m_begin) {
    return pop_front();
  } else if (node == m_end) {
    return pop_back();
  } else {
    CarNode* ptr = node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete ptr;
  }
}

void CarList::pop_back() {
  CarNode* ptr = m_end;
  m_end = m_end->prev;
  m_end->next = nullptr;
  delete ptr;
}

void CarList::pop_front() {
  CarNode* ptr = m_begin;
  m_begin = m_begin->next;
  m_begin->prev = nullptr;
  delete ptr;
}
