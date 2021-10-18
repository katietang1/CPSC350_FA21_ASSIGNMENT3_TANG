/*
Katie Tang
2313452
htang@chapman.edu
CPSC-350-02
Assignment 3: Game of Life
*/
/*
main.cpp prompts user for map generation method then calls functions accordingly
*/
#include <iostream>
#include "generateGrid.h"

using namespace std;

int main(int argc, char **argv){
    string mapPref; 
    cout << "Welcome to the Game of Life." << endl;
    cout << "Would you like to generate random map or provide a map file?" << endl;
    cout << "'r' or 'f'" << endl;
    cin >> mapPref;
        if (mapPref == "r") {
            generateGrid *gg = new generateGrid();
            gg->randomGrid(mapPref);
            delete gg;
            

        } else if (mapPref == "f"){
            generateGrid *gg = new generateGrid();
            gg->fileGrid(mapPref);
            delete gg;

        }

    return 0;

}

