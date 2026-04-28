#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RecipeTemplate {
protected:
  vector<string> ingredients;

public:
  RecipeTemplate(const vector<string>& ingredients) {
    this->ingredients = ingredients;
  }

  void listIngredients() {
    cout << "Ingredients:\n";
    for (const string& ingredient : ingredients) {
      cout << "- " << ingredient << endl;
    }
  }
  virtual void prepareRecipe() = 0;

  void serve() {
    cout << "Serve the dish.\n";
  }

  virtual void makeRecipe() final {
    listIngredients();
    prepareRecipe();
    serve();
    cout << endl;
  }

  virtual ~RecipeTemplate() {}
};


class CakeRecipe : public RecipeTemplate {
public:
  CakeRecipe() : RecipeTemplate({"flour", "sugar", "eggs", "milk", "butter"}) {}

  void prepareRecipe() override {
    cout << "Mix ingredients." << endl;
    cout << "Put the mixture into a baking form." << endl;
    cout << "Bake the cake." << endl;
  }
};

class SaladRecipe : public RecipeTemplate {
public:
  SaladRecipe() : RecipeTemplate({"tomatoes", "cucumbers", "lettuce", "oil", "salt"}) {}

  void prepareRecipe() override {
    cout << "Wash the vegetables." << endl;
    cout << "Cut the vegetables." << endl;
    cout << "Mix everything with oil and salt." << endl;
  }
};


int main() {
  CakeRecipe cake;
  SaladRecipe salad;

  cout << "Cake recipe:" << endl;
  cake.makeRecipe();

  cout << "Salad recipe:" << endl;
  salad.makeRecipe();

  return 0;
}