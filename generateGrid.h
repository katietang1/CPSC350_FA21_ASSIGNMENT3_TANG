/*
Katie Tang
2313452
htang@chapman.edu
CPSC-350-02
Assignment 3: Game of Life
*/
#ifndef GENERATEGRID_H
#define GENERATEGRID_H

#include <iostream>
#include "generateGrid.h"
#include<cstdlib>

using namespace std;

class generateGrid{
    public:

    generateGrid();
    ~generateGrid();

    void randomGrid(std::string mapPref);
    void fileGrid(std::string mapPref);
    void gameMode();
    void classicMap();
    void donutMap();
    void mirrorMap();

    bool startGame(char choice);




};


#endif