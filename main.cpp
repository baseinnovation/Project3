#include <iostream>
#include <fstream>

using namespace std;

class Recipe{
public:
    string name;
    string id;
    string cookTime;
    string authorName;
    string totalRatings;
    string rating;
    string calories;
    string sugar;
    string protein;
    string servings;
};

void PrintRecipe(Recipe& _recipe){
    cout << "Name: " << _recipe.name << endl;
    cout << "Rating: " << _recipe.rating << endl;
    cout << "Total Ratings: " << _recipe.totalRatings << endl;
    cout << "Cook Time: " << _recipe.cookTime << endl;
    cout << "Calories: " << _recipe.calories << endl;
    cout << "Servings: " << _recipe.servings;
}

void GatherData(string location){
    ifstream file(location);
    string data;
    //removing the top line
    //cout << data;
   int i = 0;
    if(file.is_open()){
        while(!file.fail()){
            Recipe newRecipe;
            string DataVar;
            i++;

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

            //getting the protein count
            getline(file, DataVar, ',');
            newRecipe.protein = DataVar;

            //getting servings
            getline(file, DataVar, ',');
            newRecipe.servings = DataVar;


            //thai
            //japanese
            //indian
            //vegan
            //mexican
            //australian
            //

            //deciding to leave out the instructions string cause at the top the new recipe wont start until a string starts with an id

            //testing to see if the data was gathered correctly
            //PrintRecipe(newRecipe);



            //THIS REACHES THE END OF GATHERING THE DATA FOR THE NEWRECIPE OBJ
            //THE NAME OF THE NEW RECIPE IS 'newRecipe' and it is a Recipe Data Object

            //BEGIN THE AREA WHERE YOU MAKE THE DATA STRUCTURES AND CLASSES TO STORE THE NEW RECIPE

            PrintRecipe(newRecipe);

            cout << endl << endl;

        }
    }
}

int main() {

    GatherData("../recipes.csv");

    return 0;
}
