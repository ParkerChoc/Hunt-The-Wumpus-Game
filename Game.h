/******************************************************
** Program: Game.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Game class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Game
#define H_Game

#include <iostream>
#include "Map.h"
#include "Player.h"
#include <unistd.h> //used for user input
#include <termios.h> //used for user input
#include <stdlib.h> // Used for rand

using namespace std;

class Game
{
    private:
        //player start coordinates
        int p_x;
        int p_y;
        //wumpus start coordinates
        int w_x;
        int w_y;
        //gold start coordinates
        int g_x;
        int g_y;
        //other game variables
        Map my_map;
        Player user;
        int arrows;
        bool debug;
    public:
    //Constructors
        Game(const int&, bool);
    //User input
        char getch();
    //Other functions
        void player_shoot();
        void robot_shoot();
        void player_input();
        void robot_input();
        void print_status();
        void game_flow();
    //restarting the game
        void randomize(const int&);
        void reset();
};

#endif