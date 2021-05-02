#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "car_list.h"

// I'm so lazy to create the iterator for this container
// + iterator to iterate only through specific models hmmm

typedef std::vector<std::string> Words;
const Words model_names = {"Skoda", "Bentley", "Polestar", "Dodge",
"Volvo", "Landwind", "Rimac", "Acura", "Tata", "Proton", "Audi",
"BMW", "Bugatti", "Cherry", "Chevrolet", "Citroen", "Ferrari", "GAZ",
"Honda", "Hyondai", "Jaguar", "Landrover", "Lexus", "Mitsubishi",
"Mazda", "Nissan", "Renault", "Seat", "Senova", "Suzuki", "Toyota", "Volkswagen"};
const Words countries = {"Albania", "Afghanistan", "Russia", "Ukrain", "France",
  "Japan", "China", "South_Korea", "North_Korea", "India", "Moldova", "Belarus",
  "USA", "Canada", "Brazilia", "UK", "Spain", "Italy", "Norway", "Denmark",
  "Portugal", "Czech", "Litva", "Latvia", "Egypt", "Tunis", "Turkey", "Germany",
  "Austria", "MOTHERLAND"};

CarData getRandomCarData() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0,
      std::min(model_names.size() - 1, countries.size() - 1));
  return {model_names[dist(gen)],
    countries[dist(gen)],
    1700 + dist(gen)*dist(gen) + dist(gen)};
}

void debugList(const CarList& list) {
  list.printList();
  std::cout << std::endl;
}
// Tester main
/*
int main() {
  constexpr size_t size = 15;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, size);
  for (int step = 1; step < 3; ++step) {
    std::cout << step << " test\n";
    CarList list;
    for (size_t i = 0; i < size; ++i) {
      list.push_front(getRandomCarData());
    }
    list.sort();
    ModelList mlist = list.createModelList();
    int id = dist(gen);
    auto ptr = mlist.getFirstNode(list[id].car_model);
    std::string car_model = ptr->data.car_model;
    std::cout << "All elements with car model = " << car_model << '\n';
    for (; ptr && ptr->data.car_model == car_model; ptr = ptr->next) {
      std::cout << ptr->data << std::endl;
    }
    int id2 = dist(gen);
    car_model = list[id2].car_model;
    list.insert_model({car_model, "IMPOSTER", 2000});
    std::cout << "List with inserted IMPOSTER with car_model = " << car_model
      << '\n';
    debugList(list);
    int id3 = dist(gen);
    car_model = list[id3].car_model;
    std::cout << "List without models with name = " << car_model
      << '\n';
    list.delete_model(car_model);
    debugList(list);
  }
  return 0;
}
*/
// Menu main
int main() {
  int number_of_operation;
  CarList* list = nullptr;
  ModelList model_list;
  std::string model_name, country;
  int prod_year;
  std::cout << "Welcome to my program 'Auto model linked list' ! ";
  while (true) {
    std::cout << "Choose your next operation:\n"
      << "1 - create a new list\n"
        << "2 - add element at the end of the list (parameters: model name, country, production year)\n"
        << "3 - add element at the beginning of the list (parameters: model name, country, production year)\n"
        << "4 - print list in normal order\n"
        << "5 - print list in reverse order\n"
        << "6 - delete last list element\n"
        << "7 - print first element with specific model name\n"
        << "8 - sort list\n"
        << "Next operations will work correctly only if the list is sorted:\n"
        << "9 - add element by its model name (parameters: model name, country, production year)\n"
        << "10 - create models list based on the current list\n"
        << "11 - delete all models from the list (parameter - model name)\n";
    std::cin >> number_of_operation;

    switch(number_of_operation) {
      case 1:
        list = new CarList();
        break;
      case 2:
        std::cin >> model_name >> country >> prod_year;
        list != nullptr ?
          list->push_back({model_name, country, prod_year}) : void();
        break;
      case 3:
        std::cin >> model_name >> country >> prod_year;
        list != nullptr ?
          list->push_front({model_name, country, prod_year}) : void();
        break;
      case 4:
        list != nullptr ? list->printList() : void();
        break;
      case 5:
        list != nullptr ? list->reversePrintList() : void();
        break;
      case 6:
        list != nullptr ? list->pop_back() : void();
        break;
      case 7:
        std::cin >> model_name;
        if (list != nullptr) {
          auto ptr = list->searchByModel(model_name);
          std::cout << "Element: " << ptr->data << '\n';
        }
        break;
      case 8:
        list != nullptr ? list->sort() : void();
        break;
      case 9:
        std::cin >> model_name >> country >> prod_year;
        list != nullptr ?
          list->insert_model({model_name, country, prod_year}) : void();
        break;
      case 10:
        std::cin >> model_name;
        model_list = list != nullptr ?
          list->createModelList() : ModelList();
        break;
      case 11:
        std::cin >> model_name;
        list != nullptr ? list->delete_model(model_name) : void();
    }
    std::cout << '\n';
  }
  std::cout << "See you next time!" << std::endl;
  return 0;
}
