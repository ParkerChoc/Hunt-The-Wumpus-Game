/******************************************************
** Program: Room.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Room class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Room
#define H_Room

using namespace std;

#include <iostream>
#include "Event.h"

class Room
{
    private:
        bool has_player;
        bool debug;
        char event_inside;
        Event* whats_inside;
    public:
    //Constructors
        Room();
    //Getters
        Event* get_event();
        char get_event_type();
        bool contains_player();
        bool not_hallway();
        bool is_debug_mode();
    //Setters
        Room& set_event(Event*);
        void set_event_char(char);
        void set_player(bool);
        void set_debug_mode(bool);
    //Other functions
        void print_room();
};

#endif