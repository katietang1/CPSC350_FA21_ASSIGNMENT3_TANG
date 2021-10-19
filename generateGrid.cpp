/*
Katie Tang
2313452
htang@chapman.edu
CPSC-350-02
Assignment 3: Game of Life
*/
/*
generateGrid.cpp creates 2D Arrays of maps and applies boundaries,
the game is also simulated in this class.
*/

#include<iostream>
#include<fstream>
#include"generateGrid.h"
#include<ctime>
#include<cstdlib>

using namespace std;

generateGrid::generateGrid(){
    // default constructor 
}
generateGrid::~generateGrid(){
    // default destructor 
}
// global variables 
 int row;
 int col;
 double density;
 char currGen[100][100];
 int neighbors[100][100];
 int generationNum = 0;
 char referenceGen[100][100];
 bool isStable = false;
 char userPreference;
 string fileName;

// randomGrid() prompts user for grid inputs then creates a random 2D Array map
void generateGrid::randomGrid(string mapPref){
    if (mapPref == "r"){ 
        // prompt for dimensions and density
        cout << "Please enter the number of rows: " << endl;
        cin >> row;
        cout << "Please enter the number of rows: " << endl;
        cin >> col;
        cout << "Please enter population density: " << endl;
        cin >> density;
        
        int i = 0;
        int j = 0;
        int arraySize = row * col;
        int numofX = arraySize * density;
        srand(time(NULL));
        for (int l = 0; l < row; l++){
            for (int k = 0; k < col; k++){
                currGen[l][k] = '-';
            }
        }
        for (int m = 0; m < numofX; m++){
            i = rand()%row;
            j = rand()%col;
            if (currGen[i][j] == 'X'){
                m--;
                continue;
            }
            currGen[i][j] = 'X';
        }
        cout << "GENERATION 0: " << endl;
         for(i = 0; i<row; i++){
             for(j = 0; j<col; j++){
                 cout << currGen[i][j];
             }
             cout << endl;
        }
    } 
    gameMode();
}

//fileGrid() prompts user for filepath then reads the file and creates 2D Array map
void generateGrid::fileGrid(string mapPref){
    if (mapPref == "f"){
        // prompt for filepath 
        cout << "Please enter a file path: " << endl;
        std::string filePath;
        cin.ignore(1000,'\n');
        getline(cin, filePath);
        ifstream file;
        file.open(filePath);
        if (!file){
            cout << "Invalid file" << endl;
        }
        file >> row >> col;
        int i = 0;
        int j = 0;
        while (!file.eof()){
            file >> currGen[i][j];
            j++;
            if (j >= col){
                j = 0;
                i++;
            } 
        }
       
        cout << "GENERATION 0: " << endl;
         for(i = 0; i<row; i++){
            for(j = 0; j<col; j++){
                cout << currGen[i][j];
            }
            cout << endl;
        }
    }
    gameMode();
}

//gameMode() prompt user for boundary mode then call functions accrodingly
void generateGrid::gameMode(){
    string mode;
    cout << "What boundary mode would you like to apply? c/d/m " << endl;
    cin >> mode;
    if (mode == "c"){
        classicMap();
    } 
    if (mode == "d"){
        donutMap();
    } 
    if (mode == "m"){
        mirrorMap();
    } 
}

//classicMap() computes neighbors based on surrounding locations, will stop checking if isStable() becomes true
void generateGrid::classicMap(){
    cout << "Would you like a pause, press enter between generations, or print to a text file?" << endl;
    cout << "p / e / t" << endl;
    cin >> userPreference;
    if (userPreference == 't'){
        cout << "Please enter a file name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, fileName);
    }
    while (isStable == false){
        int counter;
        for(int i = 0; i <row; i++){
            for(int j = 0; j < col; j++){
                counter = 0;
                // check -1,-1 neighbor
                if(i-1 >=0 && j-1 >=0){
                    if(currGen[i-1][j-1] == 'X'){
                    counter++;
                    }
                }
                //check -1, 0 neighbor
                if(i-1 >=0){
                    if(currGen[i-1][j] == 'X'){
                    counter++;

                    }
                }
                //check -1,1 neighbor
                if(i-1 >=0 && j+1 < col){
                    if(currGen[i-1][j+1] == 'X'){
                    counter++;
                    }

                }
                //check 0,-1 neighbor
                if(j-1 >= 0){
                    if(currGen[i][j-1] == 'X'){
                    counter++;

                    }
                }
                //check 0,+1 neighbor
                if(j+1 < col){
                    if(currGen[i][j+1] == 'X'){
                    counter++;

                    }
                }
                //check 1,0 neighbor
                if(i+1 < row){
                    if(currGen[i+1][j] == 'X'){
                    counter++;

                    }
                }
                //check 1,-1 neighbor
                if(i+1 < row && j-1 >= 0){
                    if(currGen[i+1][j-1] == 'X'){
                    counter++;

                    }
                }
                //check 1,1 neighbor
                if(i+1 < row && j+1 < col){
                    if(currGen[i+1][j+1] == 'X'){
                    counter++;

                    }
                }
                //store number of neighbors for each [i][j] in 2D Array
                neighbors[i][j] = counter;
            }
        }
        //making a reference Grid to compare before births and deaths in startGame()
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                referenceGen[i][j] = currGen[i][j];
            }
        }
        generationNum++;
        isStable = startGame(userPreference);
    }
}

//donutMap() computes neighbors based on surrounding locations and boarder wraps,  will stop checking if isStable() becomes true
void generateGrid::donutMap(){
    cout << "Would you like a pause, press enter, or print to a text file?" << endl;
    cout << "p / e / t" << endl;
    cin >> userPreference;
    if (userPreference == 't'){
        cout << "Please enter a file name" << endl;
        cin.ignore(1000, '\n');
        getline(cin, fileName);
    }
    while (isStable == false){
        int counter;
        for(int i = 0; i <row; i++){
            for(int j = 0; j < col; j++){
                counter = 0;

                // check -1,-1 neighbor
                if(i-1 >=0 && j-1 >=0){ 
                    if(currGen[i-1][j-1] == 'X'){
                    counter++;
                    }
                } else if (i-1 >=0 && j == 0){ //left boarder
                    if(currGen[i-1][col-1] == 'X'){
                    counter++;
                    }
                } else if (i == 0 && j-1 > 0 ) { //top boarder
                    if(currGen[row-1][j-1] == 'X'){
                    counter++;
                    }
                }
                else{ //top left corner
                    if (currGen[row-1][col-1] == 'X'){
                    counter++;
                    }
                }

            //check -1, 0 neighbor
                if(i-1 >=0){ 
                    if(currGen[i-1][j] == 'X'){
                    counter++;

                    } 
                }else{ //top boarder
                    if (currGen[row-1][j] == 'X'){
                    counter++;
                    }
                }

            //check -1,1 neighbor
                if(i-1 >=0 && j+1 < col){ 
                    if(currGen[i-1][j+1] == 'X'){
                    counter++;
                    }
                }else if (i == 0 && j+1 < col){ //top boarder
                    if(currGen[row-1][j+1] == 'X'){
                    counter++;
                    }
                } else if (i-1 >=0 && j + 1== col) { //right boarder
                    if(currGen[i-1][0] == 'X'){
                    counter++;
                    }
                }else{ // top right corner
                    if (currGen[row-1][0] == 'X'){
                    counter++;
                    }
                }

            //check 0,-1 neighbor
                if(j-1 >= 0){  
                    if(currGen[i][j-1] == 'X'){
                    counter++;

                    }
                }else{ // left boarder
                    if (currGen[i][col-1] == 'X'){
                    counter++;
                    }
                }

            //check 0,+1 neighbor
                if(j+1 < col){ 
                    if(currGen[i][j+1] == 'X'){
                    counter++;

                    }
                }else{ //right boarder
                    if (currGen[i][0] == 'X'){
                    counter++;
                    }
                }

            //check 1,0 neighbor
                if(i+1 < row){ 
                    if(currGen[i+1][j] == 'X'){
                    counter++;

                    }
                }else{ //bottom boarder
                    if (currGen[0][j] == 'X'){
                    counter++;
                    }
                }

            //check 1,-1 neighbor
                if(i+1 < row && j-1 >= 0){ 
                    if(currGen[i+1][j-1] == 'X'){
                    counter++;
                    }
                }else if (i + 1 == row && j-1 >= 0){ //bottom boarder
                    if(currGen[0][j-1] == 'X'){
                    counter++;
                    }
                } else if (i+1 < row && j == 0) { //left boarder
                    if(currGen[i+1][col] == 'X'){
                    counter++;
                    }
                }else{ //bottom left corner
                    if (currGen[0][col-1] == 'X'){
                    counter++;
                    }
                }
            //check 1,1 neighbor
                if(i+1 < row && j+1 < col){ 
                    if(currGen[i+1][j+1] == 'X'){
                    counter++;
                    } 
                } else if (i + 1 == row && j+1 < col){ //bottom boarder
                    if(currGen[0][j+1] == 'X'){
                    counter++;
                    }
                } else if (i+1 < row && j + 1 == col ) { //right boarder
                    if(currGen[i+1][0] == 'X'){
                    counter++;
                    }
                } else{ //bottom right corner
                    if (currGen[0][0] == 'X'){
                    counter++;
                    }
                }
                neighbors[i][j] = counter;
            }
    
        }
        //making a reference Grid to compare before births and deaths in startGame()
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                referenceGen[i][j] = currGen[i][j];
            }
        }
        generationNum++;
        isStable = startGame(userPreference);
    }
}


//mirrorMap() computes neighbors based on surrounding locations and boarder reflections  will stop checking if isStable() becomes true
void generateGrid::mirrorMap(){
    cout << "Would you like a pause, press enter, or print to a text file?" << endl;
    cout << "p / e / t" << endl;
    cin >> userPreference;
    if (userPreference == 't'){
        cout << "Please enter an output file name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, fileName);
    }
    while (isStable == false){
        int counter;
        for(int i = 0; i <row; i++){
            for(int j = 0; j < col; j++){
                counter = 0;

                // check -1,-1 neighbor
                if(i-1 >=0 && j-1 >=0){ 
                    if(currGen[i-1][j-1] == 'X'){
                    counter++;
                    }
                } else if (i-1 >=0 && j == 0){ //left boarder
                    if(currGen[i-1][j] == 'X'){
                    counter++;
                    }
                } else if (i == 0 && j-1 > 0 ) { //top boarder
                    if(currGen[i][j-1] == 'X'){
                    counter++;
                    }
                }
                else{ //top left corner
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check -1, 0 neighbor
                if(i-1 >=0){ 
                    if(currGen[i-1][j] == 'X'){
                    counter++;

                    } 
                }else{ //top boarder
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check -1,1 neighbor
                if(i-1 >=0 && j+1 < col){ 
                    if(currGen[i-1][j+1] == 'X'){
                    counter++;
                    }
                }else if (i == 0 && j+1 < col){ //top boarder
                    if(currGen[i][j+1] == 'X'){
                    counter++;
                    }
                } else if (i-1 >=0 && j +1 == col) { //right boarder
                    if(currGen[i-1][j] == 'X'){
                    counter++;
                    }
                }else{ // top right corner
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check 0,-1 neighbor
                if(j-1 >= 0){  
                    if(currGen[i][j-1] == 'X'){
                    counter++;

                    }
                }else{ // left boarder
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check 0,+1 neighbor
                if(j+1 < col){ 
                    if(currGen[i][j+1] == 'X'){
                    counter++;

                    }
                }else{ //right boarder
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check 1,0 neighbor
                if(i+1 < row){ 
                    if(currGen[i+1][j] == 'X'){
                    counter++;

                    }
                }else{ //bottom boarder
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }

            //check 1,-1 neighbor
                if(i+1 < row && j-1 >= 0){ 
                    if(currGen[i+1][j-1] == 'X'){
                    counter++;
                    }
                }else if (i + 1 == row && j-1 >= 0){ //bottom boarder
                    if(currGen[i][j-1] == 'X'){
                    counter++;
                    }
                } else if (i+1 < row && j == 0) { //left boarder
                    if(currGen[i+1][j] == 'X'){
                    counter++;
                    }
                }else{ //bottom left corner
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }
            //check 1,1 neighbor
                if(i+1 < row && j+1 < col){ 
                    if(currGen[i+1][j+1] == 'X'){
                    counter++;
                    } 
                } else if (i + 1 == row && j+1 < col){ //bottom boarder
                    if(currGen[i][j+1] == 'X'){
                    counter++;
                    }
                } else if (i+1 < row && j + 1 == col ) { //right boarder
                    if(currGen[i+1][j] == 'X'){
                    counter++;
                    }
                } else{ //bottom right corner
                    if (currGen[i][j] == 'X'){
                    counter++;
                    }
                }
                neighbors[i][j] = counter;
            }
    
        }
        //making a reference Grid to compare before births and deaths in startGame()
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                referenceGen[i][j] = currGen[i][j];
            }
        }
        generationNum++;
        startGame(userPreference);
    }
    
}
/*startGame() begins implementing rules of the game then returning each generation based on user preferences,
this function will return bool if isStable determines two grids are the same
*/
bool generateGrid::startGame(char userPreference){
    // implement game rules
    for(int i = 0; i <row; i++){
        for(int j = 0; j < col; j++){
            if (neighbors[i][j] <= 1){
                 if(currGen[i][j] == 'X'){
                    currGen[i][j] = '-';
                }
            }
            if (neighbors[i][j] == 3){
                if(currGen[i][j] == '-'){
                    currGen[i][j] = 'X';
                }
            }
            if (neighbors[i][j] >= 4){
                currGen[i][j] = '-';
            }

        }
    }
    if (userPreference == 'p'){ //pause 
        cout << "GENERATION: " << generationNum << endl;
        for(int i = 0; i<row; i++){
             for(int j = 0; j<col; j++){
                 cout << currGen[i][j];
            }
            cout << endl;
        }
        //system("pause");
        cin.get();
    }

    if (userPreference == 'e'){ // enter
        cout << "GENERATION: " << generationNum << endl;
        for(int i = 0; i<row; i++){
            for(int j = 0; j<col; j++){
                cout << currGen[i][j];
            }
            cout << endl;
        }
        cout << "Press Enter to Continue";
        cout << endl;
        cin.ignore();   
    }

    if (userPreference == 't'){ //text file
        ofstream file;
        file.open(fileName, std::ios::app);
        if(!file){
            cout << "Invalid file" << endl;
        }
        file << "GENERATION: " << generationNum << endl;
        for(int i = 0; i<row; i++){
            for(int j = 0; j<col; j++){
                file << currGen[i][j];
            }
            file << endl;
        }
        file.close();
    }

     
    //check if world has stablized by comparing referenceGrid and currGrid
   for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if (referenceGen[i][j] != currGen[i][j]){
                return false;
            }
        }
    }
    cout << "World has stablized" << endl;
    cout << "Press Enter to Exit";
    cin.ignore();
    return true;
    
}