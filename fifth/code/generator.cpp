#include <fstream>
#include <random>
#include <string>
#include <vector>

class Generator{
public:
  Generator() {
    std::ifstream fin;
    fin.open("countries");
    std::string field;
    while (std::getline(fin, field)){
      countries.push_back(field);
    }
    fin.close();
  }

  void generate(int64_t data_size, const std::string& file_name = "test.txt") {
    std::ofstream fout;
    fout.open(file_name);
    for (int i = 0; i < data_size; ++i) {
      fout << getRandomProductName() << " "
      <<  getRandomCountry() << " "
      << getRandomAmountOfTheProduct() << '\n';
    }
    fout.close();
  }

private:
  const int64_t BIG_NUM = 10'000'000;
  std::vector<std::string> countries;
  const std::vector<std::string> product_names = {
    "Apple", "Banana", "Cucumber", "Tomato",
    "Garlic", "Lemon", "Orange", "Peach",
    "Grapefruit", "Avocado", "Pear", "Black_beans",
    "White_beans", "Chickpeas", "Corn", "Beetroot",
    "Pumpkin", "Butter_squash", "Pear", "Carrot",
    "Cilantro", "Lime", "Phig", "Potato",
    "Sweet_potato", "Broccoli", "Cauliflower", "Brussel_sprouts",
    "Tomato", "Cumin", "Turnip", "Zuccini", "Coconut",
    "Parsley", "Artichok", "Peas", "Onion", "Lettuce",
    "Red_cabbage", "Spinach", "Green_beans", "Strawberry",
    "Blueberry", "Rasberry", "Ginger", "Cranberry",
    "Plume", "Prun", "Abricot", "Grape", "Raisins",
    "White_rice", "Wheat", "Rye", "Quinoa", "Bulgur",
    "Brown_rice", "Oats", "Radish", "Cinnamon",
    "Vanilla", "Sugar", "Salt", "Vinegar",
    "Olive_oil", "Sunflower_oil", "Coconut_oil",
    "Sesame_oil", "Canola_oil", "Avocado_oil",
    "Milk", "Kefir", "Heavy_cream", "Half_and_half",
    "Yogurt", "Parmesan_cheese", "Cottage_cheese",
    "Mozarella_cheese", "Cheddar_cheese",
    "Gorgonzolla_cheese", "Tofu", "Soy_beans",
    "Edamami", "Soy_sauce", "Mayonaisse", "Pumpkin_seeds",
    "Sesame_seeds", "Butter", "White_wine", "Red_wine",
    "Maple_syrup", "Jam", "Musli", "Granola",
    "Buckwheat", "All_purpose_wheat_flour", "Bread_wheat_flour",
    "Cake_wheat_flour", "Whole_wheat_flour", "Rice_flour",
    "Whole_chicken", "Whole_turkey", "Beef_back",
    "Lamb_ribs", "Pork_tenderloin", "Chicken_eggs",
    "Pineapple", "Asparagus", "Duck_breast", "Leek",
    "Bell_pepper", "Saurekrat", "Red_onion", "Chili_pepper",
    "Mango", "Watermelon", "Melon", "Scallion"
  };

  std::string getRandomCountry() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist (0, countries.size() - 1);
    return countries[dist(gen)];
  }
  
  std::string getRandomProductName() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist (0, product_names.size() - 1);
    return product_names[dist(gen)];
  }
  
  int64_t getRandomAmountOfTheProduct() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist (0, BIG_NUM);
    return dist(gen);
  }
};
