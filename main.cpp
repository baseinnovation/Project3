#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Recipe{
public:





    
    string name;
    int cookTime;
    int prepTime;
    int totalTime;
    string description;
    string keywords;
    string recipeIngredientRatios;
    string recipeIngredients;
    int totalRatings;
    float rating;
    int calories;
    int nutritionData[9] = {0};
    float foodYield;
    string instructions;
};

void PrintData(vector<Recipe> data){
    for(auto DATA: data){

    }
}

vector<Recipe> GatherData(string location){
    ifstream file(location);
    string data;
    vector<Recipe> Data;
    //removing the top line
    getline(file, data);
    if(file.is_open()){
        while(!file.fail()){
            data = "";
            getline(file, data);
            istringstream dataLine (data);
            Recipe newData;

            //to get rid of the FOODID
            string DataVar;
            getline(dataLine, DataVar, ',');

            //retrieving the name
            getline(dataLine, DataVar, ',');
            newData.name = DataVar;

            //getting rid of the authorid
            getline(dataLine, DataVar, ',');

            //getting rid of the authorname
            getline(dataLine, DataVar, ',');

            //retrieving the cooktime
            getline(dataLine, DataVar, ',');

            string cookTime = "";
            int i = 0;
            while(DataVar[i] != '\0'){
                if(isdigit(DataVar[i])){
                    cookTime += DataVar[i];
                }
                i++;
            }
            if(cookTime == ""){
                cookTime = "0";
            }







            


            newData.cookTime = stoi(cookTime);
            cout << cookTime << " :: " ;

            //retrieving prepTime;
            getline(dataLine, DataVar, ',');
            string prepTime = "";
            i = 0;
            while(DataVar[i] != '\0'){
                if(isdigit(DataVar[i])){
                    prepTime += DataVar[i];
                }
                i++;
            }
            if(prepTime == ""){
                prepTime = "0";
            }
            newData.prepTime = stoi(prepTime);

            cout << prepTime << endl;

            cout << DataVar << endl;
        }
    }
    return Data;
}

int main() {

    vector<Recipe> Data = GatherData("../recipes.csv");
    PrintData(Data);

    return 0;
}
