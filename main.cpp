#include "Bin.h"
#import <queue>
#include <time.h>
#include <cstdlib>

using namespace std;

void PrintRecipe(Recipe& _recipe){
    cout << _recipe.name << " by " << _recipe.authorName << endl;
    cout << "Rating: " << _recipe.rating << endl;
    cout << "Cook Time: " << _recipe.cookTime << " minutes" << endl;
    cout << "Calories: " << _recipe.calories << endl;
    cout << "Servings: " << _recipe.servings;
}

auto cmpRating = [](Recipe a, Recipe b){
    return a < b;
};

auto cmpTime = [](Recipe a, Recipe b){
    return a << b;
};

auto cmpCalories = [](Recipe a, Recipe b){
    return a >> b;
};

void GatherData(string location, Ordered_Map<Recipe>& Ordered_Map, Unordered_Map<Recipe>& UnorderedMap, float& UMPTime, float& BSTTime){
    ifstream file(location);
    int index = 0;
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
            string something ="";
            int timeVar = 0;
            //cout << index << endl;
            //index++;
            if(DataVar != "NA")
            for(int i = 2; i < DataVar.size(); i++){
                if(isdigit(DataVar[i])){
                    something += DataVar[i];
                }
                else{
                    if(DataVar[i] == 'M'){
                        timeVar += stoi(something);
                        something = "";
                    }
                    else if(DataVar[i] == 'H'){
                            timeVar = stoi(something) * 60;
                            something = "";
                    }
                }
            }
            newRecipe.cookTime = timeVar;

            //getting RecipeCategory
            string Category;
            getline(file, DataVar, ',');
            Category = DataVar;

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
            auto start = high_resolution_clock::now();
            UnorderedMap.insert(Category, newRecipe, newRecipe.name);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            UMPTime += duration.count();

            start = high_resolution_clock::now();
            Ordered_Map.insert(Category, newRecipe, newRecipe.name);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            BSTTime += duration.count();

            //Ordered_Map.Print();

            //BEGIN THE AREA WHERE YOU MAKE THE DATA STRUCTURES AND CLASSES TO STORE THE NEW RECIPE

        }
    }
}

int main() {

    Unordered_Map<Recipe> UnorderedMap;
    Ordered_Map<Recipe> OrderedMap;
    float InsertUMPTime = 0;
    float InsertRBTime = 0;

    GatherData("../recipes.csv", OrderedMap, UnorderedMap, InsertUMPTime, InsertRBTime);
    cout << "Time to load Ordered Map: " << InsertRBTime / 1000000.0f << " seconds" << endl;
    cout << "Time to load Unordered Map: " << InsertUMPTime / 1000000.0f << " seconds" << endl;
    cout << endl;

    cout << "Welcome to Meal Finder!" << endl << "Select the type of thing you are looking for today" << endl;

    bool good = false;
    while(!good) {
        //gather user input
        cout << "1. Meals     2. Breakfasts      3. Snacks" << endl << "4. Beverages      5. Desserts" << endl;
        string input;

        cout << "Enter Number or option: " ;
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        good = true;
        string searchoption = "";

        //find the right category
        if (input == "MEALS" || input == "MEAL" || input == "1") {
            searchoption = "Main Course";
        } else if (input == "BREAKFASTS" || input == "BREAKFAST" || input == "2") {
            searchoption = "Breakfast";
        } else if (input == "SNACKS" || input == "SNACK" || input == "3") {
            searchoption = "Snacks";
        } else if (input == "BEVERAGES" || input == "BEVERAGE" || input == "4") {
            searchoption = "Beverages";
        } else if (input == "DESSERTS" || input == "DESSERT" || input == "5") {
            searchoption = "Dessert";
        } else {
            cout << endl << "Please enter a valid option" << endl;
            good = false;
        }
        if(searchoption != "") {
            cout << endl;
            auto start = high_resolution_clock::now();
            vector<Recipe> UMPVector = UnorderedMap.find(searchoption);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time it took to retrieve info from Unordered Map: " << duration.count() / 1000.0f
                 << " milliseconds" << endl;
            start = high_resolution_clock::now();
            vector<Recipe> OMPVector = OrderedMap.search(searchoption);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Time it took to retrieve info from Ordered Map: " << duration.count() / 1000.0f << " milliseconds"
                 << endl << endl;

            string input = "";
            bool good = false;
            while (!good) {
                good = true;
                cout << "How would you like to filter the results?" << endl;
                cout << "1. Custom      2. Random Recipes" << endl;
                cout << "Enter an input: ";
                cin >> input;
                priority_queue<Recipe, vector<Recipe>, decltype(cmpRating)> RatingQueue(cmpRating);
                for (int i = 0; i < UMPVector.size(); i++) {
                    RatingQueue.push(OMPVector[i]);
                    //cout << "Pushed" << endl;
                }
                cout << endl;
                srand(time(0));

                if(input == "1"){
                    vector<Recipe> cookTimeRecipes;
                    cout << "Preferred Cook Time (minutes), (Enter -1 if no preference):";
                    string time = "";
                    cin >> time;
                    if(time != "-1")
                    for(int i = 0; i < RatingQueue.size(); i++){
                            Recipe CurRecipe = RatingQueue.top();
                            RatingQueue.pop();
                            if (abs(CurRecipe.cookTime - stoi(time)) <= 10) {
                                cookTimeRecipes.push_back(CurRecipe);
                            }
                    }
                    vector<Recipe> customRecipes;
                    cout << "Preferred Calories, (Enter -1 if no preference):";
                    string calories;
                    cin >> calories;
                    cout << endl;
                    bool check = false;
                    if(time != "-1" && calories != "-1") {
                        for (auto CurRecipe: cookTimeRecipes) {
                            if (isdigit(CurRecipe.calories[0]))
                                if (abs(stof(CurRecipe.calories) - stof(calories)) <= 100)
                                    customRecipes.push_back(CurRecipe);
                        }
                        check = true;
                    }
                    else if(time == "-1" && calories != "-1"){
                        for(int i = 0; i < RatingQueue.size(); i++){
                            Recipe CurRecipe = RatingQueue.top();
                            RatingQueue.pop();
                            if (CurRecipe.calories != "NA")
                                if (abs(stoi(CurRecipe.calories) - stoi(calories)) <= 100) {
                                    customRecipes.push_back(CurRecipe);
                                }
                        }
                        check = true;
                    }
                    else if(time != "-1" && calories == "-1"){
                        for(int i = 0; i < 5; i++){
                            PrintRecipe(cookTimeRecipes[i]);
                            cout << endl << endl;
                        }
                    }
                    else{
                        for(int i = 0; i < 5; i++){
                            for(int i = 0; i < RatingQueue.size(); i++){
                                Recipe CurrentRecipe = RatingQueue.top();
                                RatingQueue.pop();
                                if(CurrentRecipe.rating == "5"){
                                    customRecipes.push_back(CurrentRecipe);
                                }
                                else{
                                    break;
                                }
                            }
                            int random = rand() % (customRecipes.size() + 1);
                            PrintRecipe(customRecipes[random]);
                            cout << endl << endl;
                        }
                    }
                    if(check) {
                        for (int i = 0; i < 5; i++) {
                            PrintRecipe(customRecipes[i]);
                            cout << endl << endl;
                        }
                    }
                }
                else if(input == "2"){
                    for(int i = 0; i < 5; i++){
                        int random = rand() % (UMPVector.size() + 1);
                        PrintRecipe(UMPVector[random]);
                        cout << endl << endl;
                    }
                }
                else{
                    good = false;
                }

            }
        }
    }
    return 0;
}
