#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Recipe{
public:
    string name;
    string id;
    int cookTime;
    int prepTime;
    int totalTime;
    string authorName;
    int totalRatings;
    float rating;
    int calories;
    float foodYield;
    int servings;
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
            //newData.id = stoi(DataVar);

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
            for(int i = 0; i < DataVar.size(); i++){
                if(isdigit(DataVar[i])){
                    cookTime += DataVar[i];
                }
            }
            if(cookTime == ""){
                cookTime = "0";
            }

            //newData.cookTime = stoi(cookTime);
            cout << cookTime << " :: " ;

            //retrieving prepTime;
            getline(dataLine, DataVar, ',');
            string prepTime = "";
            for(int i = 0; i < DataVar.size(); i++){
                if(isdigit(DataVar[i])){
                    prepTime += DataVar[i];
                }
            }
            if(prepTime == ""){
                prepTime = "0";
            }

            cout << prepTime << endl;
            //newData.prepTime = stoi(prepTime);

            //retrieving totalTime
            getline(dataLine, DataVar, ',');
            //newData.totalTime = stoi(DataVar);

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
