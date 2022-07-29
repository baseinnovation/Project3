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
    cout << _recipe.name << " :: " << _recipe.rating << endl;
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

            cout << "Cycle: " << i << endl;
            i++;

            //getting the ID
            getline(file, DataVar, ',');
            //newData.id = stoi(DataVar)
            cout << DataVar << " :: ";

            //retrieving the name
            getline(file, DataVar, ',');
            newRecipe.name = DataVar;
            cout << DataVar << " :: ";

            //getting rid of the authorid
            getline(file, DataVar, ',');

            //getting rid of the authorname
            getline(file, DataVar, ',');

            //retrieving the cooktime
            getline(file, DataVar, ',');

            string cookTime = "";
            for(int i = 0; i < DataVar.size(); i++){
                if(isdigit(DataVar[i])){
                    cookTime += DataVar[i];
                }
            }
            if(cookTime == ""){
                cookTime = "0";
            }

            //newData.cookTime = stoi(cookTime);

            //retrieving prepTime;
            getline(file, DataVar, ',');
            string prepTime = "";
            for(int i = 0; i < DataVar.size(); i++){
                if(isdigit(DataVar[i])){
                    prepTime += DataVar[i];
                }
            }
            if(prepTime == ""){
                prepTime = "0";
            }

            //newData.prepTime = stoi(prepTime);

            //retrieving totalTime
            getline(file, DataVar, ',');
            //newData.totalTime = stoi(DataVar);

            //getting the DataPublished
            getline(file, DataVar, ',');

            //getting the Description
            getline(file, DataVar, ',');

            //getting Image

            getline(file, DataVar, ')');
            getline(file, DataVar, ',');

            //getting RecipeCategory
            getline(file, DataVar, ',');

            //getting Keywords
            getline(file, DataVar, ')');
            getline(file, DataVar, ',');

            //getting RecipeIngredientsQuantities
            getline(file, DataVar, ')');
            getline(file, DataVar, ',');

            //getting RecipeIngredientParts
            getline(file, DataVar, ')');
            getline(file, DataVar, ',');

            //getting AggregatedRating
            getline(file, DataVar, ',');
            newRecipe.rating = DataVar;

            //getting Rating Count
            getline(file, DataVar, ',');

            //getting Calories
            getline(file, DataVar, ',');

            //eliminating some of the ingredients
            for(int i = 0; i < 7; i++){
                getline(file, DataVar, ',');
            }

            //getting the protein count
            getline(file, DataVar, ',');

            //getting servings
            getline(file, DataVar, ',');

            //getting recipe yield
            getline(file, DataVar, ',');

            //instructions
            getline(file, DataVar);

            //testing to see if the data was gathered correctly
            //PrintRecipe(newRecipe);

            //THIS REACHES THE END OF GATHERING THE DATA FOR THE NEWRECIPE OBJ
            //THE NAME OF THE NEW RECIPE IS 'newRecipe' and it is a Recipe Data Object

            //BEGIN THE AREA WHERE YOU MAKE THE DATA STRUCTURES AND CLASSES TO STORE THE NEW RECIPE

            cout << endl << endl;

        }
    }
    return Data;
}

int main() {

    GatherData("../recipes.csv");

    return 0;
}
