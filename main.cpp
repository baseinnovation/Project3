#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Recipe{
public:
    string name;
    string id;
    string cookTime;
    string prepTime;
    string totalTime;
    string authorName;
    string totalRatings;
    string rating;
    string calories;
    string foodYield;
    string servings;
};

void PrintRecipe(Recipe& _recipe){
    cout << "Name: " << _recipe.name << endl;
    cout << "Rating: " << _recipe.rating << endl;
    cout << "Total Ratings: " << _recipe.totalRatings << endl;
    cout << "Prep Time: " << _recipe.prepTime << endl;
    cout << "Cook Time: " << _recipe.cookTime << endl;
    cout << "Calories: " << _recipe.calories << endl;
    cout << "Servings: " << _recipe.servings;
}

vector<Recipe> GatherData(string location){
    ifstream file(location);
    string data;
    vector<Recipe> Data;
    //removing the top line
    getline(file, data);
    //cout << data;
   int i = 0;
    if(file.is_open()){
        while(!file.fail()){
            Recipe newRecipe;
            string DataVar;
            i++;

            //getting the ID
            getline(file, DataVar, ',');
            while(!isdigit(DataVar[1])){
                getline(file, DataVar, ',');
            }
            newRecipe.id = DataVar;


            //retrieving the name
            getline(file, DataVar, ',');
            newRecipe.name = DataVar;

            //getting rid of the authorid
            getline(file, DataVar, ',');

            //getting rid of the authorname
            getline(file, DataVar, ',');

            //retrieving the cooktime
            getline(file, DataVar, ',');
            newRecipe.cookTime = DataVar;

            //retrieving prepTime;
            getline(file, DataVar, ',');
            newRecipe.prepTime = DataVar;

            //retrieving totalTime
            getline(file, DataVar, ',');
            newRecipe.totalTime = DataVar;


            //getting the DataPublished
            getline(file, DataVar, ',');


            //getting the Description
            getline(file, DataVar, ',');
            while(DataVar[0] != '"'){
                getline(file, DataVar, ',');
            }


            //getting Image
            if(DataVar[0] == '"'){
                getline(file, DataVar, ')');
                getline(file, DataVar, ',');
            }


            //getting RecipeCategory
            getline(file, DataVar, ',');

            //getting Keywords
            getline(file, DataVar, ',');
            if(DataVar[0] == '"'){
                getline(file, DataVar, ')');
                getline(file, DataVar, ',');
            }


            //getting RecipeIngredientsQuantities
            getline(file, DataVar, ',');
            //cout << "Qualities " << DataVar << endl;
            if(DataVar[0] == '"'){
                getline(file, DataVar, ')');
                getline(file, DataVar, ',');
            }

            //getting RecipeIngredientParts
            getline(file, DataVar, ',');
            if(DataVar[0] == '"'){
                getline(file, DataVar, ')');
                getline(file, DataVar, ',');
            }

            //getting AggregatedRating
            getline(file, DataVar, ',');
            newRecipe.rating = DataVar;

            //getting Rating Count
            getline(file, DataVar, ',');
            newRecipe.totalRatings = DataVar;

            //getting Calories
            getline(file, DataVar, ',');
            newRecipe.calories = DataVar;

            //eliminating some of the ingredients
            for(int i = 0; i < 7; i++){
                getline(file, DataVar, ',');
            }

            //getting the protein count
            getline(file, DataVar, ',');

            //getting servings
            getline(file, DataVar, ',');
            newRecipe.servings = DataVar;

            //getting recipe yield
            getline(file, DataVar, ',');

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
    return Data;
}

int main() {

    GatherData("../recipes.csv");

    return 0;
}
