/******************************************************
** Program: Player.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Player class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Player
#define H_Player

using namespace std;
#include <iostream>

#include "Map.h"

class Player
{
    private:
        int x;
        int y;
    public:
        //non - private game states for easier interaction
        bool alive;
        bool has_gold;
        bool has_killed_wumpus;
    //Constructors
        Player();
        Player(int&, int&);
    //Getters
        int get_x();
        int get_y();
    //Setters
        void set_coordinates(int&, int&);
        void reset_stats();
    //Other functions
        void trigger_adjacent_rooms(Map&);
        void trigger_my_room(Map&);
        void move(Map&, int, int);
        void shoot(Map&, int, int, int);
};

#endif