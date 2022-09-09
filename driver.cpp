/******************************************************
** Program: driver.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: main driver program for assignment 4
** Input: two command line arguments: int size of map,
**  and int debug
** Output: depends
******************************************************/

#include <iostream>
#include "Game.h"
using namespace std;

int main(int num_arguments, const char** argv)
{
    /*
    **  Command arguments: 
    **  0: ./doit 
    **  1: size_of_map  (int)
    **  2: debug        (bool)
    */
    int size_of_map = atoi(argv[1]);
    bool debug = atoi(argv[2]);
    char answer;
    Game my_game(size_of_map, debug);
    do
    {   
        my_game.game_flow();
        cout << "Enter what do you wish to do:\n";
        cout << "(r): new game with random configuration\n";
        cout << "(s): new game with same configuration\n";
        cout << "(q): quit and exit this program\n";   
        cin >> answer;
        if (answer == 's')
            my_game.reset();
        if (answer == 'r')
            my_game.randomize(size_of_map);
    } while (answer != 'q');
    return 0;
}