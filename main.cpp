#include "Bin.h"

using namespace std;

void PrintRecipe(Recipe& _recipe){
    cout << "Name: " << _recipe.name << endl;
    cout << "Rating: " << _recipe.rating << endl;
    cout << "Total Ratings: " << _recipe.totalRatings << endl;
    cout << "Cook Time: " << _recipe.cookTime << endl;
    cout << "Calories: " << _recipe.calories << endl;
    cout << "Servings: " << _recipe.servings;
}

void GatherData(string location, Ordered_Map<Recipe>& Ordered_Map, Unordered_Map<Recipe>& UnorderedMap, float UMPTime, float BSTTime){
    ifstream file(location);
    if(file.is_open()){
        while(!file.fail()){
            Recipe newRecipe;
            string DataVar;

            //getting the ID
            getline(file, DataVar, ',');
            newRecipe.id = DataVar;

            //retrieving the name
            getline(file, DataVar, ',');
            newRecipe.name = DataVar;

            //getting rid of the authorname
            getline(file, DataVar, ',');
            newRecipe.authorName = DataVar;

            //retrieving the cooktime
            getline(file, DataVar, ',');
            newRecipe.cookTime = DataVar;

            //getting RecipeCategory
            string Category;
            getline(file, DataVar, ',');
            Category = DataVar;

            //getting Keywords
            string allKeys;
            getline(file, DataVar, ')');
            allKeys = DataVar;
            getline(file, DataVar, ',');

            //getting AggregatedRating
            getline(file, DataVar, ',');
            newRecipe.rating = DataVar;

            //getting Rating Count
            getline(file, DataVar, ',');
            newRecipe.totalRatings = DataVar;

            //getting Calories
            getline(file, DataVar, ',');
            newRecipe.calories = DataVar;

            //getting FatContent
            getline(file, DataVar, ',');

            //getting sat
            getline(file, DataVar, ',');

            //getting cholesterol
            getline(file, DataVar, ',');

            //getting sodium carbs
            getline(file, DataVar, ',');

            //getting fiber
            getline(file, DataVar, ',');

            //getting sugar
            getline(file, DataVar, ',');
            newRecipe.sugar = DataVar;

            //getting the protein count
            getline(file, DataVar, ',');
            newRecipe.protein = DataVar;

            //getting servings
            getline(file, DataVar, ',');
            newRecipe.servings = DataVar;

            //THIS REACHES THE END OF GATHERING THE DATA FOR THE NEWRECIPE OBJ
            //THE NAME OF THE NEW RECIPE IS 'newRecipe' and it is a Recipe Data Object

            //cout << "Gathered data" << endl;
            UnorderedMap.insert(Category, newRecipe, newRecipe.name);
            Ordered_Map.insert(Category, newRecipe, newRecipe.name);

            //BEGIN THE AREA WHERE YOU MAKE THE DATA STRUCTURES AND CLASSES TO STORE THE NEW RECIPE

        }
    }
}

int main() {

    Unordered_Map<Recipe> UnorderedMap;
    Ordered_Map<Recipe> OrderedMap;
    float InsertUMPTime;
    float InsertRBTime;

    GatherData("../recipes.csv", OrderedMap, UnorderedMap, InsertUMPTime, InsertRBTime);

    cout << "Welcome to Meal Finder!" << endl << "Select the type of thing you are looking for today" << endl;

    bool good = false;
    while(!good) {
        //gather user input
        cout << "1. Meals     2. Breakfasts      3. Snacks" << endl << "4. Beverages      5. Snacks" << endl;
        string input;

        cout << "Enter Number or option: " ;
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        good = true;

        //find the right category
        if (input == "MEALS" || input == "MEAL" || input == "1") {
            vector<Recipe> breakfastlist = UnorderedMap.find("Main Course");
            for(int i = 0; i < breakfastlist.size(); i++){
                cout << breakfastlist[i].name << endl;
            }
        } else if (input == "BREAKFASTS" || input == "BREAKFAST" || input == "2") {
            vector<Recipe> breakfastlist = UnorderedMap.find("Breakfast");
            for(int i = 0; i < breakfastlist.size(); i++){
                cout << breakfastlist[i].name << endl;
            }
        } else if (input == "SNACKS" || input == "SNACK" || input == "3") {
            vector<Recipe> breakfastlist = UnorderedMap.find("Snacks");
            for(int i = 0; i < breakfastlist.size(); i++){
                cout << breakfastlist[i].name << endl;
            }
        } else if (input == "BEVERAGES" || input == "BEVERAGE" || input == "4") {
            vector<Recipe> breakfastlist = UnorderedMap.find("Beverages");
            for(int i = 0; i < breakfastlist.size(); i++){
                cout << breakfastlist[i].name << endl;
            }
        } else if (input == "DESSERTS" || input == "DESSERT" || input == "5") {
            vector<Recipe> breakfastlist = UnorderedMap.find("Dessert");
            for(int i = 0; i < breakfastlist.size(); i++){
                cout << breakfastlist[i].name << endl;
            }
        } else {
            cout << endl;
            cout << "Please choose a valid input" << endl;
            good = false;
        }
    }


    return 0;
}
