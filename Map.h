/******************************************************
** Program: Map.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Map class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Map
#define H_Map

using namespace std;

#include <iostream>
#include <vector>
#include <stdlib.h> // Used for rand

#include "Room.h"
#include "Bats.h"
#include "Pit.h"
#include "Wumpus.h"
#include "Gold.h"

class Map
{
    private:
        int size_of_map;
        vector<vector<Room>> grid;
        Bats b1;
        Pit p1;
        Gold g1;
        Wumpus w1;
    public:
    //Constructors
        Map();
        Map(const int&);
    //Getters
        int get_size();
    //Operator overload
        Room& operator()(int, int);
    //Other functions
        bool border_check(int, int);
        Map& fill_rooms(bool);
        void swap_rooms(Room*, Room*);
        void find_rand_hallway(int&, int&);
        void find_rand_room(int&, int&);
        void player_drop(int&, int&, bool, bool);
        void find_type(int&, int&, char);
        void shuffle(int&, int&, int&, int&);
        void print_map();
        void wumpus_moves();
        void reset_stuff(int&, int&, int&, int&, bool);
};

#endif